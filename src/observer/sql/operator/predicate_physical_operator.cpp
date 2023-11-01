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
// Created by WangYunlai on 2022/6/27.
//

#include "common/log/log.h"
#include "sql/operator/predicate_physical_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"
#include "sql/expr/tuple.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  RC rc;
  trx_ = trx;
  // open operator of sub-query in expression
  // Generate physical operators for sub-query stored in expression, the expre is a ConjunctionExpr
  if (expression_.get()->type() == ExprType::CONJUNCTION) {
    ConjunctionExpr                          *conj_expr   = static_cast<ConjunctionExpr *>(expression_.get());
    std::vector<std::unique_ptr<Expression>> &child_exprs = conj_expr->children();
    for (int i = 0; i < child_exprs.size(); i++) {
      if (child_exprs[i]->type() == ExprType::COMPARISON) {
        ComparisonExpr *comp_expr = static_cast<ComparisonExpr *>(child_exprs[i].get());
        if (comp_expr->left()->type() == ExprType::SUB_QUERY) {  // this expre contain sub-query
          // restore physocal operator
          OperExpr                    *oper_expr  = static_cast<OperExpr *>((comp_expr->left()).get());
          unique_ptr<PhysicalOperator> &physic_oper = oper_expr->get_physic_oper();

          // open
          rc = physic_oper.get()->open(trx);
          if (rc != RC::SUCCESS)
            return rc;
        }
        if (comp_expr->right()->type() == ExprType::SUB_QUERY) {  // this expre contain sub-query
          // restore physocal operator
          OperExpr                    *oper_expr  = static_cast<OperExpr *>((comp_expr->right()).get());
          unique_ptr<PhysicalOperator> &physic_oper = oper_expr->get_physic_oper();

          // open
          rc = physic_oper.get()->open(trx);
          if (rc != RC::SUCCESS)
            return rc;
        }
      }
    }
  } else if (expression_.get()->type() ==
             ExprType::COMPARISON) {  // there are only one expression, then the conjunctionExpre is removed
    ComparisonExpr *comp_expr = static_cast<ComparisonExpr *>(expression_.get());
    if (comp_expr->left()->type() == ExprType::SUB_QUERY) {  // this expre contain sub-query
      // restore physocal operator
      OperExpr                    *oper_expr  = static_cast<OperExpr *>((comp_expr->left()).get());
      unique_ptr<PhysicalOperator> &physic_oper = oper_expr->get_physic_oper();

      // open
      rc = physic_oper.get()->open(trx);
      if (rc != RC::SUCCESS)
        return rc;
    }
    if (comp_expr->right()->type() == ExprType::SUB_QUERY) {  // this expre contain sub-query
      // restore physocal operator
      OperExpr                    *oper_expr  = static_cast<OperExpr *>((comp_expr->right()).get());
      unique_ptr<PhysicalOperator> &physic_oper = oper_expr->get_physic_oper();

      // open
      rc = physic_oper.get()->open(trx);
      if (rc != RC::SUCCESS)
        return rc;
    }
  }

  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC PredicatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  oper->set_parent_query_tuples(get_parent_query_tuples());
  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    // append current tuple into parent query tuples
    std::unordered_map<std::string, Tuple *> parent_query_tuples = get_parent_query_tuples();
    std::string table_name = dynamic_cast<RowTuple *>(tuple)->get_table_name();
    parent_query_tuples[table_name] = tuple;
    expression_->set_parent_query_tuples(parent_query_tuples);

    Value value;
    rc = expression_->get_value(*tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple()
{
  return children_[0]->current_tuple();
}
