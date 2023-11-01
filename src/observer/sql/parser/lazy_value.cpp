#include "sql/parser/lazy_value.h"
#include "sql/expr/tuple.h"

void LazyValue::lazy_execution()
{
  is_executed_ = true;
  if (physical_operator_ == nullptr) {
    execution_result_ = RC::INTERNAL;
    LOG_WARN("The phycical operator not init, please check again");
    return;
  }

  auto rc = physical_operator_->open(nullptr);
  if (rc != RC::SUCCESS) {
    execution_result_ = rc;
    return;
  }

  rc = physical_operator_->next();
  if (rc == RC::RECORD_EOF) {
    physical_operator_->close();
    execution_result_ = RC::SUCCESS;
    value_.set_isnull();
    return;
  }

  auto tuple = physical_operator_->current_tuple();
  rc         = tuple->cell_at(0, value_);
  if (rc != RC::SUCCESS) {
    physical_operator_->close();
    execution_result_ = rc;
    return;
  }

  rc = physical_operator_->next();
  if (rc != RC::RECORD_EOF) {
    physical_operator_->close();
    execution_result_ = RC::MULTI_ROW_RETURN;
    return;
  }
  execution_result_ = RC::SUCCESS;
  physical_operator_->close();
}