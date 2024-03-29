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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"

RC ProjectPhysicalOperator::open(Trx *trx)
{
  trx_ = trx;

  for (int i = 0; i < tuple_.cell_num(); i++) {
    TupleCellSpec *spec = nullptr;
    tuple_.cell_spec_at(i, spec);
    if (!spec->is_expr() || !spec->expr()->is_const_value()) {
      is_all_constant_ = false;
    }
  }

  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty()) {
    if (is_all_constant_ && !is_executed_) {
      is_executed_ = true;
      return RC::SUCCESS;
    } else {
      return RC::RECORD_EOF;
    }
  }
  children_[0]->set_parent_query_tuples(get_parent_query_tuples());
  return children_[0]->next();
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  if (!is_all_constant_) {
    tuple_.set_tuple(children_[0]->current_tuple());
  } else {
    tuple_.set_tuple(new ProjectTuple());
  }
  return &tuple_;
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::add_projection(const Table *table, Field &field)
{
  // FOR AGGR FUNC
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec;
  if (field.get_aggr_type() == AggregationType::COUNT && field.meta() == nullptr)
    // count(*)
    spec = new TupleCellSpec("COUNT(*)");
  else
    spec = new TupleCellSpec(table->name(), field.field_name(), field.field_name());
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::add_projection(Expression *expr)
{
  TupleCellSpec *spec = new TupleCellSpec(expr);
  tuple_.add_cell_spec(spec);
}
