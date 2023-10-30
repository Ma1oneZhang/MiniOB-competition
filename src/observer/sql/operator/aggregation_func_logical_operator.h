/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */
#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"

/**
 * @brief 表示聚合函数算子
 * @details 表示聚合函数算子
 * @ingroup LogicalOperator
 */
class AggregationLogicalOperator : public LogicalOperator
{
public:
  AggregationLogicalOperator(Table *tables, const std::vector<Field> &fields, const std::vector<Field> &group_by);
  virtual ~AggregationLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::AGGREGATION; }

  const Table        *tables() const { return tables_; }
  std::vector<Field> &field() { return fields_; }
  std::vector<Field> &group_by_fields() { return group_by_fields_; }

private:
  Table *tables_;
  // 聚合函数所需要聚合的字段
  std::vector<Field> fields_;
  std::vector<Field> group_by_fields_;
};
