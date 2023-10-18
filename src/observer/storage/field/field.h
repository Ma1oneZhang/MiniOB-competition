/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/table/table.h"
#include "storage/field/field_meta.h"
#include <cassert>

/**
 * @brief 字段
 *
 */
class Field
{
public:
  Field() = default;
  Field(const Table *table, const FieldMeta *field, const AggregationType aggr = AggregationType::NONE)
      : table_(table), field_(field), aggregation_(aggr)
  {
    if (aggr != AggregationType::NONE) {
      if (field_ == nullptr) {
        aggr_field_name_ = "*";
      } else {
        aggr_field_name_ = field_->name();
      }
      switch (aggregation_) {
        case AggregationType::MAX: {
          aggr_field_name_ = "MAX(" + aggr_field_name_ + ")";
        } break;
        case AggregationType::MIN: {
          aggr_field_name_ = "MIN(" + aggr_field_name_ + ")";
        } break;
        case AggregationType::COUNT: {
          aggr_field_name_ = "COUNT(" + aggr_field_name_ + ")";
        } break;
        case AggregationType::AVG: {
          aggr_field_name_ = "AVG(" + aggr_field_name_ + ")";
        } break;
        case AggregationType::SUM: {
          aggr_field_name_ = "SUM(" + aggr_field_name_ + ")";
        } break;

        case AggregationType::NONE: {
          LOG_PANIC("WARN_AGGREGATION_TYPE");
        } break;
      }
    }
  }
  Field(const Field &) = default;

  const Table     *table() const { return table_; }
  const FieldMeta *meta() const { return field_; }

  AttrType attr_type() const { return field_->type(); }

  const char *table_name() const { return table_->name(); }
  const char *field_name() const
  {
    return AggregationType::NONE == aggregation_ ? field_->name() : aggr_field_name_.c_str();
  }

  void set_table(const Table *table) { this->table_ = table; }
  void set_field(const FieldMeta *field) { this->field_ = field; }
  void set_int(Record &record, int value);
  void set_aggr_type(AggregationType type) { this->aggregation_ = type; }

  AggregationType get_aggr_type() const { return aggregation_; }
  int             get_int(const Record &record);

  const char *get_data(const Record &record);

private:
  const Table     *table_ = nullptr;
  const FieldMeta *field_ = nullptr;
  std::string      aggr_field_name_;
  AggregationType  aggregation_ = AggregationType::NONE;
};
