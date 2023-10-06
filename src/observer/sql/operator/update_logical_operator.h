#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/parser/value.h"
#include "storage/table/table.h"

class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const char *attribute_name, Value *values, int value_amount);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table      *table() const { return table_; }
  const char *attr_name() { return attribute_name_; }
  Value      *values() { return values_; }
  int         value_amount() { return value_amount_; }

private:
  Table      *table_          = nullptr;
  const char *attribute_name_ = nullptr;
  Value      *values_         = nullptr;
  int         value_amount_   = 0;
};