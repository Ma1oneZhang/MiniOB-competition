#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/parser/value.h"
#include "storage/table/table.h"

class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<std::string> *attribute_names, Value *values, int value_amount);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table                    *table() const { return table_; }
  std::vector<std::string> *attr_names() { return attribute_names_; }
  Value                    *values() { return values_; }
  int                       value_amount() { return value_amount_; }

private:
  Table                    *table_           = nullptr;
  std::vector<std::string> *attribute_names_ = nullptr;
  Value                    *values_          = nullptr;
  int                       value_amount_    = 0;
};