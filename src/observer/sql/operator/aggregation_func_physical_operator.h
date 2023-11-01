#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/trx/trx.h"

#include <cstdint>
#include <unordered_map>

struct AggregationResult
{
  // for count
  size_t tot_count_ = 0;
  // for sum
  int64_t int_sum_      = 0;
  double  float_sum_    = 0;
  bool    is_float_sum_ = false;
  bool    is_null       = false;
  // for min max
  Value max_or_min{};
  bool  first = true;
};

// create a map class with an interface designed for computing aggregations.
class SimpleAggregationMap
{
public:
  SimpleAggregationMap() = default;
  RC    operator()(const std::vector<Value> &keys, Value &value, AggregationType type);
  auto &operator[](std::string key) { return map_[key]; }
  // for iterator and range-based for loop
  class iterator
  {
  public:
    iterator(std::unordered_map<std::string, std::pair<std::vector<Value>, AggregationResult>>::iterator iter)
        : iter_(iter)
    {}
    iterator &operator++()
    {
      iter_++;
      return *this;
    }
    bool operator!=(const iterator &other) const { return iter_ != other.iter_; }
    bool operator==(const iterator &other) const { return iter_ == other.iter_; }
    auto operator->() { return iter_; }
    void operator++(int) { iter_++; }

    std::pair<std::string, std::pair<std::vector<Value>, AggregationResult>> operator*() const { return *iter_; }

  private:
    std::unordered_map<std::string, std::pair<std::vector<Value>, AggregationResult>>::iterator iter_;
  };
  iterator begin() { return iterator(map_.begin()); }
  iterator end() { return iterator(map_.end()); }

private:
  RC add(const std::string &key, Value value, AggregationType type);
  std::unordered_map<std::string, std::pair<std::vector<Value>, AggregationResult>> map_;
};

class AggregationPhysicalOperator : public PhysicalOperator
{
public:
  AggregationPhysicalOperator(std::vector<Field> &fields, std::vector<Field> &group_by)
      : aggr_fields_(fields), group_by_fields_(group_by)
  {
    // get aggregation field type num
    int aggr_field_type_num = 0;
    for (auto &field : fields) {
      if (field.get_aggr_type() != AggregationType::NONE) {
        aggr_field_type_num++;
      }
    }
    for (int i = 0; i < aggr_field_type_num; i++) {
      maps_.emplace_back();
    }
  }
  virtual ~AggregationPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGGREGATION; }

  RC open(Trx *trx) override;
  RC open() override { return open(trx_); }
  RC reset()
  {
    current_tuple_ = nullptr;
    is_executed_ = false;
    return_nothing_ = false;
    sub_operator_eof_ = true;
    wild_card_count_ = 0;
    iters_.clear();
    std::vector<SimpleAggregationMap> new_map;
    for(int i=0; i<maps_.size(); i++) new_map.emplace_back();
    maps_ = new_map;
    return RC::SUCCESS;
  }
  
  RC close() override;
  RC next() override;

  Tuple *current_tuple() override { return current_tuple_; }

private:
  void next_result()
  {
    for (auto &iter : iters_) {
      iter++;
    }
  }
  Tuple                                      *current_tuple_ = nullptr;
  std::vector<Field>                          aggr_fields_;
  std::vector<Field>                          group_by_fields_;
  bool                                        is_executed_      = false;
  Trx                                        *trx_              = nullptr;
  bool                                        return_nothing_   = false;
  bool                                        sub_operator_eof_ = true;
  int                                         wild_card_count_;
  std::vector<SimpleAggregationMap>           maps_;
  std::vector<SimpleAggregationMap::iterator> iters_;
};
