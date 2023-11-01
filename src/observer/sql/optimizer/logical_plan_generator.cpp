/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "sql/operator/aggregation_func_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/update_logical_operator.h"

#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include <memory>
#include <utility>
#include <vector>

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc                  = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc                      = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc                      = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc                      = create_plan(delete_stmt, logical_operator);
    } break;
    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc                        = create_plan(explain_stmt, logical_operator);
    } break;
    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc                      = create_plan(update_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);
  unique_ptr<LogicalOperator> aggregation_oper(nullptr);
  unique_ptr<LogicalOperator> having_oper(nullptr);

  const std::vector<Table *> &tables     = select_stmt->tables();
  const std::vector<Field>   &all_fields = select_stmt->query_fields();

  std::vector<Field> fields;
  std::vector<Field> group_by;
  bool               aggr = false;
  for (Table *table : tables) {
    for (const Field &field : all_fields) {
      if (field.get_aggr_type() != AggregationType::NONE) {
        aggr = true;
      }
      // count(*)
      if (field.get_aggr_type() == AggregationType::COUNT && field.table() == nullptr) {
        fields.push_back(field);
      } else if (field.is_expr()) {
      } else if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true /*readonly*/));
    for (const Field &field : all_fields) {
      if (!field.is_expr() && 0 == strcmp(field.table_name(), table->name()) && field.get_aggr_type() == AggregationType::NONE) {
        group_by.push_back(field);
      }
    }
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  if (aggr) {
    auto fields_ = fields;
    fields_.insert(fields_.begin(), select_stmt->having().begin(), select_stmt->having().end());
    unique_ptr<LogicalOperator> aggr_oper(new AggregationLogicalOperator(fields_, group_by));
    aggregation_oper.swap(aggr_oper);
  }

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }
  // if order by not nullptr
  unique_ptr<LogicalOperator> order_by_oper(nullptr);
  if (select_stmt->order_by_stmt()) {
    order_by_oper = make_unique<OrderByLogicalOperator>(select_stmt->order_by_stmt()->get_order_by_units());
  }
  // if having not nullptr
  if (select_stmt->having_stmt()) {
    rc = create_plan(select_stmt->having_stmt(), having_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create having logical plan. rc=%s", strrc(rc));
      return rc;
    }
  }
  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(all_fields));
  if (aggregation_oper) {
    if (predicate_oper) {
      // must have table scan operation
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      aggregation_oper->add_child(std::move(predicate_oper));
      if (having_oper) {
        having_oper->add_child(std::move(aggregation_oper));
        project_oper->add_child(std::move(having_oper));
      } else {
        project_oper->add_child(std::move(aggregation_oper));
      }
    } else {
      aggregation_oper->add_child(std::move(table_oper));
      if (having_oper) {
        having_oper->add_child(std::move(aggregation_oper));
        project_oper->add_child(std::move(having_oper));
      } else {
        project_oper->add_child(std::move(aggregation_oper));
      }
    }
  } else if (order_by_oper) {
    if (predicate_oper) {
      // must have table scan operation
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      order_by_oper->add_child(std::move(predicate_oper));
      project_oper->add_child(std::move(order_by_oper));
    } else {
      order_by_oper->add_child(std::move(table_oper));
      project_oper->add_child(std::move(order_by_oper));
    }
  } else {
    if (predicate_oper) {
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      project_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        project_oper->add_child(std::move(table_oper));
      }
    }
  }

  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  ConjunctionExpr::Type               link_type =
      filter_stmt->get_link_type() == 0 ? ConjunctionExpr::Type::AND : ConjunctionExpr::Type::OR;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    // unique_ptr<Expression> left(filter_obj_left.is_attr
    //                                 ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
    //                                 : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));
    // unique_ptr<Expression> right(filter_obj_right.is_attr
    //                                  ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
    //                                  : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));

    // filter_obj_left could be value, attr and sub_query
    unique_ptr<Expression>      left;
    unique_ptr<LogicalOperator> left_sub_query_oper(nullptr);
    switch (filter_obj_left.is_attr) {
      case 0: left.reset(static_cast<Expression *>(new ValueExpr(filter_obj_left.value))); break;
      case 1: left.reset(static_cast<Expression *>(new FieldExpr(filter_obj_left.field))); break;
      case 2: {
        switch (filter_obj_left.sub_query->type()) {
          case StmtType::CALC:
            create_plan(dynamic_cast<CalcStmt *>(filter_obj_left.sub_query), left_sub_query_oper);
            break;
          case StmtType::SELECT:
            create_plan(dynamic_cast<SelectStmt *>(filter_obj_left.sub_query), left_sub_query_oper);
            break;
          // case StmtType::PREDICATE:
          //   create_plan(dynamic_cast<FilterStmt *>(filter_obj_left.sub_query), left_sub_query_oper); break;
          case StmtType::INSERT:
            create_plan(dynamic_cast<InsertStmt *>(filter_obj_left.sub_query), left_sub_query_oper);
            break;
          case StmtType::DELETE:
            create_plan(dynamic_cast<DeleteStmt *>(filter_obj_left.sub_query), left_sub_query_oper);
            break;
          case StmtType::UPDATE:
            create_plan(dynamic_cast<UpdateStmt *>(filter_obj_left.sub_query), left_sub_query_oper);
            break;
        }
        // OperExpr* sub_query_oper = new OperExpr(sub_query_oper);
        left.reset(static_cast<Expression *>(new OperExpr(left_sub_query_oper)));
      } break;
      case 3: left.reset(static_cast<Expression *>(new ValueListExpr(filter_obj_left.value_list))); break;
      case 4: left.reset(filter_obj_left.expr_);
      default: break;
    }

    // filter_obj_right could be value, attr and sub_query
    unique_ptr<Expression>      right;
    unique_ptr<LogicalOperator> right_sub_query_oper(nullptr);
    switch (filter_obj_right.is_attr) {
      case 0: right.reset(static_cast<Expression *>(new ValueExpr(filter_obj_right.value))); break;
      case 1: right.reset(static_cast<Expression *>(new FieldExpr(filter_obj_right.field))); break;
      case 2: {
        switch (filter_obj_right.sub_query->type()) {
          case StmtType::CALC:
            create_plan(dynamic_cast<CalcStmt *>(filter_obj_right.sub_query), right_sub_query_oper);
            break;
          case StmtType::SELECT:
            create_plan(dynamic_cast<SelectStmt *>(filter_obj_right.sub_query), right_sub_query_oper);
            break;
          // case StmtType::PREDICATE:
          //   create_plan(dynamic_cast<FilterStmt *>(filter_obj_right.sub_query), right_sub_query_oper); break;
          case StmtType::INSERT:
            create_plan(dynamic_cast<InsertStmt *>(filter_obj_right.sub_query), right_sub_query_oper);
            break;
          case StmtType::DELETE:
            create_plan(dynamic_cast<DeleteStmt *>(filter_obj_right.sub_query), right_sub_query_oper);
            break;
          case StmtType::UPDATE:
            create_plan(dynamic_cast<UpdateStmt *>(filter_obj_right.sub_query), right_sub_query_oper);
            break;
        }
        // OperExpr* sub_query_oper = new OperExpr(sub_query_oper);
        right.reset(static_cast<Expression *>(new OperExpr(right_sub_query_oper)));
      } break;
      case 3: right.reset(static_cast<Expression *>(new ValueListExpr(filter_obj_right.value_list))); break;
      case 4: right.reset(filter_obj_right.expr_);
      default: break;
    }

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(link_type, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                *table = insert_stmt->table();
  vector<vector<Value>> values(*insert_stmt->values());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, std::move(values));
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = delete_stmt->table();
  FilterStmt        *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt                       *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC                          rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  auto               table       = update_stmt->table();
  auto               filter_stmt = update_stmt->filter();
  auto               attr_name   = update_stmt->attribute_names();
  auto               value       = update_stmt->values();
  std::vector<Field> fields;
  // need optimize
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  for (LazyValue &value : *value) {
    if (value.get_select_stmt() != nullptr) {
      create(value.get_select_stmt(), value.get_logical_operator());
    }
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = RC::SUCCESS;
  if (filter_stmt != nullptr)
    rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, std::move(*attr_name), std::move(*value)));
  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return RC::SUCCESS;
}
