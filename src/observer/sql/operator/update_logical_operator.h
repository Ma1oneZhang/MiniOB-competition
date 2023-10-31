#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/parser/lazy_value.h"
#include "storage/table/table.h"

class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<std::string> &&attribute_names, std::vector<LazyValue> &&lazy_values);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table                    *table() const { return table_; }
  std::vector<std::string> &attr_names() { return attribute_names_; }
  std::vector<LazyValue>   &values() { return values_; }
  int                       value_amount() { return values_.size(); }

private:
  Table                   *table_ = nullptr;
  std::vector<std::string> attribute_names_{};
  std::vector<LazyValue>   values_{};
};