#pragma once

#include "sql/operator/delete_physical_operator.h"
#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;

class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, const char *attribute_name, Value *values, int value_amount)
      : table_(table), attribute_name_(attribute_name), values_(values), value_amount_(value_amount)
  {}
  virtual ~UpdatePhysicalOperator() = default;
  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table      *table_          = nullptr;
  Trx        *trx_            = nullptr;
  const char *attribute_name_ = nullptr;
  Value      *values_         = nullptr;
  int         value_amount_   = 0;
};