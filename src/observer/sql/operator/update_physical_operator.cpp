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
    for (size_t i = 0; i < attribute_names_->size(); i++) {
      // find offset
      auto field       = table_->table_meta().field(attribute_names_->at(i).c_str());
      auto attr_len    = field->len();
      auto attr_offset = field->offset();
      ASSERT(attr_len == values_[0].length(), "The data type must have same length");

      // update null bitmap
      if (field->nullable()) {
        int  field_index        = table_->table_meta().field_index(attribute_names_->at(i).c_str());
        int  null_bitmap_offset = table_->table_meta().null_bitmap_offset();
        int  null_bitmap_size   = table_->table_meta().null_bitmap_size();
        char null_bitmap        = *(record.data() + null_bitmap_offset + null_bitmap_size - 1 - field_index / 8);
        if (values_[i].get_isnull()) {
          null_bitmap |= (1 << (field_index % 8));
        } else {
          null_bitmap &= ~(1 << (field_index % 8));
        }
        memcpy(record.data() + null_bitmap_offset + null_bitmap_size - 1 - field_index / 8, &null_bitmap, 1);
      } else if (values_[i].get_isnull()) {
        return RC::FIELD_COULD_NOT_BE_NULL;
      }
      // check the field is same, if is same, we dont need do any thing
      if (memcmp(record.data() + attr_offset, values_[i].data(), attr_len) == 0) {
        // do nothing
        continue;
      } else {
        memcpy((record.data() + attr_offset), values_[i].data(), attr_len);
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