#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/value.h"
#include "storage/trx/trx.h"
#include <cstring>
#include <memory>

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }
  std::unique_ptr<PhysicalOperator> &child = children_.front();
  RC                                 rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;
  return RC::SUCCESS;
}
RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  PhysicalOperator *child = children_.front().get();
  child->set_parent_query_tuples(get_parent_query_tuples());
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    Record    old_record;
    char     *old_record_data = new char[record.len()];
    memcpy(old_record_data, record.data(), record.len());
    old_record.set_data_owner(old_record_data, record.len());
    old_record.set_rid(record.rid());
    for (size_t i = 0; i < attribute_names_.size(); i++) {
      // find offset
      auto  field       = table_->table_meta().field(attribute_names_.at(i).c_str());
      auto  attr_len    = field->len();
      auto  attr_offset = field->offset();
      Value value;
      auto  rc = values_[i].try_get_value(value);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      value.match_field_type(field->type());
      // update null bitmap
      if (field->nullable()) {
        int  field_index        = table_->table_meta().field_index(attribute_names_.at(i).c_str());
        int  null_bitmap_offset = table_->table_meta().null_bitmap_offset();
        int  null_bitmap_size   = table_->table_meta().null_bitmap_size();
        char null_bitmap        = *(record.data() + null_bitmap_offset + null_bitmap_size - 1 - field_index / 8);
        if (value.get_isnull()) {
          null_bitmap |= (1 << (field_index % 8));
        } else {
          null_bitmap &= ~(1 << (field_index % 8));
        }
        memcpy(record.data() + null_bitmap_offset + null_bitmap_size - 1 - field_index / 8, &null_bitmap, 1);
      } else if (value.get_isnull()) {
        return RC::FIELD_COULD_NOT_BE_NULL;
      }
      if (field->type() == TEXTS) {
        auto text_buffer_pool_ = table_->get_text_buffer_pool();
        // TEXT
        Value text_val = value;
        // upper
        auto                 required_num_of_page = (text_val.length() + BP_PAGE_DATA_SIZE - 1) / BP_PAGE_DATA_SIZE;
        std::vector<Frame *> frame_list(required_num_of_page, nullptr);
        std::vector<int>     frame_num_list;
        size_t               offset = 0;
        for (int i = 0; i < required_num_of_page; i++) {
          text_buffer_pool_->allocate_page(&frame_list[i]);
          memcpy(frame_list[i]->page().data,
              value.data() + offset,
              (value.length() - offset > BP_PAGE_DATA_SIZE ? BP_PAGE_DATA_SIZE : text_val.length() - offset));
          if (value.length() - offset < BP_PAGE_DATA_SIZE) {
            memset(frame_list[i]->page().data + (value.length() - offset),
                0,
                BP_PAGE_DATA_SIZE - (value.length() - offset));
          }
          offset += BP_PAGE_DATA_SIZE;
          frame_num_list.push_back(frame_list[i]->page_num());
          frame_list[i]->mark_dirty();
          text_buffer_pool_->unpin_page(frame_list[i]);
        }
        *(int *)(record.data() + field->offset()) = required_num_of_page;
        memcpy(
            record.data() + field->offset() + sizeof(int), frame_num_list.data(), required_num_of_page * sizeof(int));
        memset(record.data() + field->offset() + sizeof(int) + required_num_of_page * sizeof(int),
            -1,                                         // all 1 in bit exprssion
            (9 - required_num_of_page) * sizeof(int));  // rest of all
        continue;
      }
      // check the field is same, if is same, we dont need do any thing
      if (memcmp(record.data() + attr_offset, value.data(), attr_len) == 0) {
        // do nothing
        continue;
      } else {
        memset(record.data() + attr_offset, 0, attr_len);
        memcpy((record.data() + attr_offset), value.data(), min(attr_len, value.length()));
      }
    }
    rc = trx_->update_record(table_, old_record, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }
  return RC::RECORD_EOF;
}
RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    for (auto &child : children_) {
      child->close();
    }
  }
  return RC::SUCCESS;
}