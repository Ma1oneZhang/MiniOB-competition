#pragma once

#include "sql/operator/physical_operator.h"
#include <cstdint>

struct AggregationResult
{
  // for count
  size_t tot_count_ = 0;
  // for sum
  int64_t int_sum_      = 0;
  double  float_sum_    = 0;
  bool    is_float_sum_ = false;
  // for min max
  Value max_or_min;
  bool  first = true;
};

class AggregationPhysicalOperator : public PhysicalOperator
{
public:
  AggregationPhysicalOperator(std::vector<Field> &fields) : fields_(fields), already_run_(false) {}
  virtual ~AggregationPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGGREGATION; }

  RC open(Trx *trx) override;
  RC open() override {
    close();
    return open(trx_);}
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return current_tuple_; }

private:
  Tuple                         *current_tuple_ = nullptr;
  const std::vector<Field>       fields_;
  std::vector<AggregationResult> result_;
  bool                           already_run_;
  Trx                           *trx_;
};