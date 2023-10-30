#include "aggregation_func_physical_operator.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"

RC AggregationPhysicalOperator::open(Trx *trx)
{
  for (auto &child : children_) {
    auto rc = child->open(trx);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC AggregationPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;

  if (!is_executed_) {
    auto child = children_[0].get();
    while (RC::SUCCESS == (rc = child->next())) {
      sub_operator_eof_ = false;
      Tuple *tuple      = child->current_tuple();
      if (nullptr == tuple) {
        LOG_WARN("failed to get current record: %s", strrc(rc));
        return rc;
      }
      // for each field
      std::vector<Value> group_by_values;
      if (!group_by_fields_.empty()) {
        for (auto field : group_by_fields_) {
          Value value;
          tuple->find_cell({field.table_name(), field.field_name()}, value);
          group_by_values.push_back(value);
        }
      } else {
        Value value;
        value.set_int(0);
        group_by_values.push_back(value);
      }
      bool is_all_null = true;
      for (auto &value : group_by_values) {
        if (!value.get_isnull()) {
          is_all_null = false;
          break;
        }
      }
      // for each field
      for (auto field : aggr_fields_) {
        if (std::string(field.field_name()) == std::string("COUNT(*)")) {
          auto v  = Value{};
          auto rc = map_(group_by_values, v, AggregationType::COUNT);
        } else if (is_all_null) {
          continue;
        } else if (field.get_aggr_type() != AggregationType::NONE) {
          Value value;
          auto  rc = tuple->find_cell({field.table_name(), field.meta()->name()}, value);
          if (rc != RC::SUCCESS) {
            LOG_WARN("Can't get value from tuple");
            return rc;
          }
          if (value.get_isnull()) {
            continue;
          }
          rc = map_(group_by_values, value, field.get_aggr_type());
          if (rc != RC::SUCCESS) {
            return rc;
          }
        }
      }
    }
    if (sub_operator_eof_) {
      Value value;
      value.set_int(0);
      map_[value.data()].second.tot_count_ = 0;
    }
    iter_ = map_.begin();
  }

  if (iter_ == map_.end()) {
    return RC::RECORD_EOF;
  }
  // start build a tuple
  auto               tuple_ptr = new AggregationTuple;
  std::vector<Value> result;
  is_executed_ = true;
  int pos      = 0;

  // select a, count(id) from group_by group by a having count(id) > 2;
  // if empty table
  // return nothing
  if (!group_by_fields_.empty() && sub_operator_eof_) {
    return RC::RECORD_EOF;
  }

  // get aggr result
  for (size_t i = 0; i < aggr_fields_.size(); i++) {
    tuple_ptr->add_cell_spec(aggr_fields_[i].field_name());
    const auto &aggr_result = iter_->second.second;
    switch (aggr_fields_[i].get_aggr_type()) {
      case AggregationType::MAX:
      case AggregationType::MIN: {
        if (aggr_result.first == true) {
          Value value;
          value.set_isnull();
          result.push_back(value);
        } else {
          result.push_back(aggr_result.max_or_min);
        }
      } break;
      case AggregationType::COUNT: {
        Value res;
        res.set_int(aggr_result.tot_count_);
        result.push_back(res);
      } break;
      case AggregationType::AVG: {
        if (aggr_result.first == true) {
          Value value;
          value.set_isnull();
          result.push_back(value);
        } else {
          Value res;
          res.set_float(aggr_result.float_sum_ / aggr_result.tot_count_);
          result.push_back(res);
        }
      } break;
      case AggregationType::SUM: {
        if (aggr_result.first == true) {
          Value value;
          value.set_isnull();
          result.push_back(value);
        } else {
          Value res;
          if (aggr_result.is_float_sum_)
            res.set_float(aggr_result.float_sum_);
          else
            res.set_int(aggr_result.int_sum_);
          result.push_back(res);
        }
      } break;
      case AggregationType::NONE: {
        auto t = iter_->second.first;
        result.push_back(iter_->second.first[pos++]);
      } break;
    };
  }
  // iterate to next result
  iter_++;
  tuple_ptr->set_cells(result);
  current_tuple_ = tuple_ptr;
  return RC::SUCCESS;
}
RC AggregationPhysicalOperator::close()
{
  if (!children_.empty()) {
    auto rc = children_[0]->close();
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  delete current_tuple_;
  return RC::SUCCESS;
}

RC SimpleAggregationMap::add(const std::string &key, Value value, AggregationType type)
{
  switch (type) {
    case AggregationType::MAX: {
      if (value.get_isnull()) {
        map_[key].second.max_or_min.set_isnull();
      }
      if (map_[key].second.max_or_min.get_isnull()) {
        break;
      } else if (map_[key].second.first) {
        map_[key].second.max_or_min = value;
        map_[key].second.first      = false;
      } else if (map_[key].second.max_or_min.compare(value) < 0) {
        map_[key].second.max_or_min = value;
      }
    } break;
    case AggregationType::MIN: {
      if (value.get_isnull()) {
        map_[key].second.max_or_min.set_isnull();
      }
      if (map_[key].second.max_or_min.get_isnull()) {
        break;
      } else if (map_[key].second.first) {
        map_[key].second.max_or_min = value;
        map_[key].second.first      = false;
      } else if (map_[key].second.max_or_min.compare(value) > 0) {
        map_[key].second.max_or_min = value;
      }
    } break;
    case AggregationType::COUNT: {
      map_[key].second.first = false;  // indicate there are values not NULL
      map_[key].second.tot_count_++;
    } break;
    case AggregationType::AVG: {
      // get count
      map_[key].second.first = false;  // indicate there are values not NULL
      map_[key].second.tot_count_++;
      value.match_field_type(AttrType::FLOATS);
      map_[key].second.float_sum_ += value.get_float();
    } break;
    case AggregationType::SUM: {
      map_[key].second.first = false;  // indicate there are values not NULL
      switch (value.attr_type()) {
        case INTS: {
          map_[key].second.int_sum_ += value.get_int();
          map_[key].second.is_float_sum_ = false;
        } break;
        case FLOATS: {
          map_[key].second.float_sum_ += value.get_float();
          map_[key].second.is_float_sum_ = true;
        } break;
        case CHARS: {
          value.match_field_type(AttrType::FLOATS);
          map_[key].second.float_sum_ += value.get_float();
          map_[key].second.is_float_sum_ = true;
        } break;
        default: {
          return RC::UNIMPLENMENT;
        } break;
      }
      // todo
    } break;
    case AggregationType::NONE: {
      return RC::UNIMPLENMENT;
    } break;
  }
  return RC::SUCCESS;
}

RC SimpleAggregationMap::operator()(const std::vector<Value> &keys, Value &value, AggregationType type)
{
  if (value.get_isnull()) {
    return RC::SUCCESS;
  }
  std::string key;
  for (auto &k : keys) {
    key += k.data();
  }
  map_[key].first = keys;
  return add(key, value, type);
}