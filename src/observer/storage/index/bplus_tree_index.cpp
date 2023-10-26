/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/index/bplus_tree_index.h"
#include "common/log/log.h"
#include "storage/common/meta_util.h"
#include <sstream>
#include <string>
#include <unistd.h>

BplusTreeIndex::~BplusTreeIndex() noexcept { close(); }

RC BplusTreeIndex::create(
    const char *file_name, const IndexMeta &index_meta, std::vector<const FieldMeta *> const &field_metas)
{
  if (inited_) {
    stringstream ss;
    index_meta.desc(ss);
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s, field:%s",
        file_name,
        index_meta.name(),
        ss.str().c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas);

  RC rc = index_handler_.create(file_name, field_metas, index_meta.is_unique());
  if (RC::SUCCESS != rc) {
    stringstream ss;
    index_meta.desc(ss);
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name,
        index_meta.name(),
        ss.str().c_str(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  stringstream ss;
  index_meta.desc(ss);
  LOG_INFO(
      "Successfully create index, file_name:%s, index:%s, field:%s", file_name, index_meta.name(), ss.str().c_str());
  return RC::SUCCESS;
}

RC BplusTreeIndex::open(
    const char *file_name, const IndexMeta &index_meta, std::vector<const FieldMeta *> const &field_meta)
{
  if (inited_) {
    stringstream ss;
    index_meta.desc(ss);
    LOG_WARN("Failed to open index due to the index has been initedd before. file_name:%s, index:%s, field:%s",
        file_name,
        index_meta.name(),
         ss.str().c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_meta);

  RC rc = index_handler_.open(file_name);
  if (RC::SUCCESS != rc) {
    stringstream ss;
    index_meta.desc(ss);
    LOG_WARN("Failed to open index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name,
        index_meta.name(),
        ss.str().c_str(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  stringstream ss;
  LOG_INFO(
      "Successfully open index, file_name:%s, index:%s, field:%s", file_name, index_meta.name(), ss.str().c_str());
  return RC::SUCCESS;
}

RC BplusTreeIndex::close()
{
  if (inited_) {
    stringstream ss;
    index_meta_.desc(ss);
    LOG_INFO("Begin to close index, index:%s, field:%s", index_meta_.name(), ss.str().c_str());
    index_handler_.close();
    inited_ = false;
  }
  LOG_INFO("Successfully close index.");
  return RC::SUCCESS;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid)
{

  // make fixed key
  int key_length{};
  for (auto &field : field_meta_) {
    key_length += field.len();
  }
  auto data  = make_unique<char>(key_length);
  key_length = 0;
  for (auto &field : field_meta_) {
    memcpy(data.get() + key_length, record + field.offset(), field.len());
    key_length += field.len();
  }
  auto rc = index_handler_.insert_entry(data.get(), rid);
  return rc;
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid)
{
  // make fixed key
  int key_length{};
  for (auto &field : field_meta_) {
    key_length += field.len();
  }
  auto data  = make_unique<char>(key_length);
  key_length = 0;
  for (auto &field : field_meta_) {
    memcpy(data.get() + key_length, record + field.offset(), field.len());
    key_length += field.len();
  }
  auto rc = index_handler_.delete_entry(data.get(), rid);
  return rc;
}

IndexScanner *BplusTreeIndex::create_scanner(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(index_handler_);
  RC rc = index_scanner->open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete index_scanner;
    return nullptr;
  }
  return index_scanner;
}

RC BplusTreeIndex::sync() { return index_handler_.sync(); }

RC BplusTreeIndex::drop(const char *base_dir, const char *table_name)
{
  ASSERT(inited_, "The Index must be inited");
  index_handler_.close();
  auto table_index_file_ = table_index_file(base_dir, table_name, index_meta().name());
  unlink(table_index_file_.c_str());
  if (EEXIST == errno) {
    LOG_ERROR("Failed to delete index file. %s, EEXIST, %s", table_index_file_.c_str(), strerror(errno));
    return RC::FILE_CLOSE;
  }
  return RC::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeHandler &tree_handler) : tree_scanner_(tree_handler) {}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept { tree_scanner_.close(); }

RC BplusTreeIndexScanner::open(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  return tree_scanner_.open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

RC BplusTreeIndexScanner::next_entry(RID *rid) { return tree_scanner_.next_entry(*rid); }

RC BplusTreeIndexScanner::destroy()
{
  delete this;
  return RC::SUCCESS;
}
