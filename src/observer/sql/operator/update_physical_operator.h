#pragma once

#include "sql/operator/delete_physical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/lazy_value.h"
#include "storage/record/record_manager.h"

class Trx;
class UpdateStmt;

class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, std::vector<std::string> &&attribute_names, std::vector<LazyValue> &&values)
      : table_(table), attribute_names_(attribute_names)
  {
    values_.swap(values);
  }
  virtual ~UpdatePhysicalOperator() = default;
  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC open() override {close(); return open(trx_);}
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  RecordFileScanner        record_scanner_;
  Table                   *table_ = nullptr;
  Trx                     *trx_   = nullptr;
  std::vector<std::string> attribute_names_{};
  std::vector<LazyValue>   values_{};
};