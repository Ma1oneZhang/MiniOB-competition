/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <cerrno>
#include <cstring>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <unistd.h>

#include "common/defs.h"
#include "storage/table/table.h"
#include "common/rc.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/record/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/index.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/trx/trx.h"

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (std::vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(int32_t table_id, const char *path, const char *name, const char *base_dir, int attribute_count,
    const AttrInfoSqlNode attributes[])
{

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p", name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(table_id, name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string        data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm       = BufferPoolManager::instance();
  rc                           = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::drop()
{
  // we checked the name in stmt creation, so we needn't check again.
  LOG_INFO("Begin to drop table %s:%s", base_dir_.c_str(), table_meta_.name());

  LOG_INFO("Begin to drop Index of table %s", table_meta_.name());
  for (auto index : indexes_) {
    auto rc = index->drop(base_dir_.c_str(), table_meta_.name());
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  indexes_.clear();
  LOG_INFO("End to drop index of table");
  data_buffer_pool_->close_file();
  unlink(table_meta_file(base_dir_.c_str(), table_meta_.name()).c_str());
  if (EEXIST == errno) {
    LOG_ERROR("Drop Table %s error", table_meta_.name());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  // remove data file
  unlink(table_data_file(base_dir_.c_str(), table_meta_.name()).c_str());
  if (EEXIST == errno) {
    LOG_ERROR("Drop Table %s error", table_meta_.name());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  return RC::SUCCESS;
}
RC Table::open(const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  std::fstream fs;
  std::string  meta_file_path = std::string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta               *index_meta = table_meta_.index(i);
    std::vector<const FieldMeta *> field_metas;
    for (auto &i : index_meta->field()) {
      const FieldMeta *field_meta = table_meta_.field(i.c_str());
      if (field_meta == nullptr) {
        LOG_ERROR("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                name(), index_meta->name(), i.c_str());
        // skip cleanup
        //  do all cleanup action in destructive Table function
        return RC::INTERNAL;
      }
    }
    BplusTreeIndex *index      = new BplusTreeIndex();
    std::string     index_file = table_index_file(base_dir, name(), index_meta->name());
    rc                         = index->open(index_file.c_str(), *index_meta, field_metas);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%s",
                name(), index_meta->name(), index_file.c_str(), strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  return rc;
}

RC Table::insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  for (int i = 0; i < indexes_.size(); i++) {
    auto index = indexes_[i];
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {  // 可能出现了键值重复
      for (int j = i - 1; j >= 0; j--) {
        auto index = indexes_[j];
        rc = index->delete_entry(record.data(), &record.rid());
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc, strrc(rc));
        }
      }
      rc = record_handler_->delete_record(&record.rid());
      if (rc != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc, strrc(rc));
      }
      return RC::RECORD_DUPLICATE_KEY;
    }
  }
  // rc = insert_entry_of_indexes(record.data(), record.rid());
  // if (rc != RC::SUCCESS) {  // 可能出现了键值重复
  //   RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/);
  //   if (rc2 != RC::SUCCESS) {
  //     LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
  //               name(), rc2, strrc(rc2));
  //   }
  //   rc2 = record_handler_->delete_record(&record.rid());
  //   if (rc2 != RC::SUCCESS) {
  //     LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
  //               name(), rc2, strrc(rc2));
  //   }
  // }
  return rc;
}

RC Table::visit_record(const RID &rid, bool readonly, std::function<void(Record &)> visitor)
{
  return record_handler_->visit_record(rid, readonly, visitor);
}

RC Table::get_record(const RID &rid, Record &record)
{
  const int record_size = table_meta_.record_size();
  char     *record_data = (char *)malloc(record_size);
  ASSERT(nullptr != record_data, "failed to malloc memory. record data size=%d", record_size);

  auto copier = [&record, record_data, record_size](Record &record_src) {
    memcpy(record_data, record_src.data(), record_size);
    record.set_rid(record_src.rid());
  };
  RC rc = record_handler_->visit_record(rid, true /*readonly*/, copier);
  if (rc != RC::SUCCESS) {
    free(record_data);
    LOG_WARN("failed to visit record. rid=%s, table=%s, rc=%s", rid.to_string().c_str(), name(), strrc(rc));
    return rc;
  }

  record.set_data_owner(record_data, record_size);
  return rc;
}

RC Table::recover_insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->recover_insert_record(record.data(), table_meta_.record_size(), record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  for (int i = 0; i < indexes_.size(); i++) {
    auto index = indexes_[i];
    index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      for (int j = i - 1; j >= 0; j--) {
        auto index = indexes_[j];
        rc         = index->delete_entry(record.data(), &record.rid());
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc, strrc(rc));
        }
      }
      rc = record_handler_->delete_record(&record.rid());
      if (rc != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc, strrc(rc));
      }
    }
  }
  return rc;
}

const char *Table::name() const { return table_meta_.name(); }

const char *Table::alias() const { return table_meta_.alias(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

RC Table::make_record(int value_num, const Value *values, Record &record)
{
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value     &value = values[i];

    if(value.get_isnull()){
      continue;
    }

    if (field->type() != value.attr_type()) {
      LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
                table_meta_.name(), field->name(), field->type(), value.attr_type());
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // 复制所有字段的值
  int   record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);
  int   null_bitmap_offset = table_meta_.null_bitmap_offset();
  int   null_bitmap_size = table_meta_.null_bitmap_size();
  char  null_bitmap[null_bitmap_size];
  memset(null_bitmap, 0, null_bitmap_size);
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field    = table_meta_.field(i + normal_field_start_index);
    const Value     &value    = values[i];
    size_t           copy_len = field->len();

    // set null bitmap
    if (value.get_isnull()) {
      null_bitmap[i / 8] |= (1 << (i % 8));      
    } else {
      null_bitmap[i / 8] &= ~(1 << (i % 8));
    }

    if (field->type() == CHARS) {
      const size_t data_len = value.length();
      if (copy_len > data_len) {
        copy_len = data_len + 1;
      }
    }
    if (value.get_isnull()) {
      // magic number 0x7F
      memset(record_data + field->offset(), 0x7f, copy_len);
    } else {
      memcpy(record_data + field->offset(), value.data(), copy_len);
    }
  }

  memcpy(record_data+null_bitmap_offset, null_bitmap, null_bitmap_size);

  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir)
{
  std::string data_file = table_data_file(base_dir, table_meta_.name());

  RC rc = BufferPoolManager::instance().open_file(data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc              = record_handler_->init(data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%s", strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner, Trx *trx, bool readonly)
{
  RC rc = scanner.open_scan(this, *data_buffer_pool_, trx, readonly, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::create_index(
    Trx *trx, std::vector<const FieldMeta *> const &field_metas, const char *index_name, bool is_unique)
{
  if (common::is_blank(index_name) || 0 == field_metas.size()) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }

  IndexMeta new_index_meta;
  RC        rc = new_index_meta.init(index_name, field_metas, is_unique);
  if (rc != RC::SUCCESS) {
    stringstream ss;
    for (auto i : field_metas) {
      ss << i->name() << ' ';
    }
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s, field_name:%s", 
             name(), index_name, ss.str().c_str());
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index      = new BplusTreeIndex();
  std::string     index_file = table_index_file(base_dir_.c_str(), name(), index_name);
  rc                         = index->create(index_file.c_str(), new_index_meta, field_metas);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, true /*readonly*/);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s", 
             name(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (scanner.has_next()) {
    rc = scanner.next(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to scan records while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);

  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  std::string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int         ret       = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);
  index->sync();
  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

RC Table::drop_index(const char *index_name)
{
  RC rc = RC::SUCCESS;
  for (auto iter = indexes_.begin(); iter != indexes_.end(); iter++) {
    if (0 == std::strcmp(index_name, (*iter)->index_meta().name())) {
      auto rc = (*iter)->drop(base_dir_.c_str(), table_meta_.name());
      if (rc != RC::SUCCESS) {
        LOG_PANIC("Delete index %s:%s ile error", table_meta_.name(), index_name);
      } else {
        TableMeta new_table_meta(table_meta_);
        new_table_meta.remove_index((*iter)->index_meta());
        indexes_.erase(iter);
        std::string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
        std::fstream fs;
        fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        if (!fs.is_open()) {
          LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
          return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
        }
        if (new_table_meta.serialize(fs) < 0) {
          LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
          return RC::IOERR_WRITE;
        }
        fs.close();
        std::string meta_file = table_meta_file(base_dir_.c_str(), name());
        int         ret       = rename(tmp_file.c_str(), meta_file.c_str());
        if (ret != 0) {
          LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
          return RC::IOERR_WRITE;
        }

        table_meta_.swap(new_table_meta);

        LOG_INFO("Successfully delete a index (%s) on the table (%s)", index_name, name());

        // new_table_meta.field_metas()
        return rc;
      }
    }
  }
  return RC::EMPTY;
}

RC Table::delete_record(const Record &record)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record.data(), &record.rid());
    ASSERT(RC::SUCCESS == rc,
        "failed to delete entry from index. table name=%s, index name=%s, rid=%s, rc=%s",
        name(),
        index->index_meta().name(),
        record.rid().to_string().c_str(),
        strrc(rc));
  }
  rc = record_handler_->delete_record(&record.rid());
  return rc;
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(std::vector<const char *> field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(),
          index->index_meta().name(),
          rc,
          strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}

RC Table::update_record(Record &old_record, Record &new_record)
{
  delete_record(old_record);
  auto rc = insert_record(new_record);
  if (rc != RC::SUCCESS) {
    delete_record(new_record);
    insert_record(old_record);
  }
  return rc;
}