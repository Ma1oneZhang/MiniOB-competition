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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/table_scan_physical_operator.h"
#include "sql/expr/tuple.h"
#include "storage/table/table.h"
#include "event/sql_debug.h"

using namespace std;

RC TableScanPhysicalOperator::open(Trx *trx)
{
  record_scanner_ = RecordFileScanner();
  RC rc = table_->get_record_scanner(record_scanner_, trx, readonly_);
  trx_  = trx;

  // open operators in sub-query
  for(auto &expr : predicates_) {
    if (expr->type() == ExprType::COMPARISON) {
      auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());

      if (comparison_expr->left()->type() == ExprType::SUB_QUERY) {  // this expre contain sub-query
        // restore physical operator
        OperExpr                    *oper_expr  = static_cast<OperExpr *>((comparison_expr->left()).get());
        unique_ptr<PhysicalOperator> &physic_oper = oper_expr->get_physic_oper();
        
        // operator.open(trx)
        rc = physic_oper->open(trx);
        if(rc != RC::SUCCESS)
          return rc;
      }

      if (comparison_expr->right()->type() == ExprType::SUB_QUERY) {  // this expre contain sub-query
        // restore physical operator
        OperExpr                    *oper_expr  = static_cast<OperExpr *>((comparison_expr->right()).get());
        unique_ptr<PhysicalOperator> &physic_oper = oper_expr->get_physic_oper();
        
        // operator.open(trx)
        rc = physic_oper->open(trx);
        if(rc != RC::SUCCESS)
          return rc;
      }
    }
  }

  return rc;
}

RC TableScanPhysicalOperator::next()
{
  if (!record_scanner_.has_next()) {
    return RC::RECORD_EOF;
  }

  RC   rc            = RC::SUCCESS;
  bool filter_result = false;
  while (record_scanner_.has_next()) {
    rc = record_scanner_.next(current_record_);

    // current_record_
    if (rc != RC::SUCCESS) {
      return rc;
    }
    auto tuple = new RowTuple();
    tuple->set_record(current_record_);
    tuple->set_schema(table_, table_->table_meta().field_metas());

    rc = filter(*tuple, filter_result);
    if (rc != RC::SUCCESS) {
      delete tuple;
      return rc;
    }

    if (filter_result) {
      tuples_.push_back(tuple);
      // LOG_WARN("get a tuple: %s", tuples_.back()->to_string().c_str());
      break;
    } else {
      // sql_debug("a tuple is filtered: %s", tuples_.back()->to_string().c_str());
      delete tuple;
      rc = RC::RECORD_EOF;
    }
  }
  return rc;
}

RC TableScanPhysicalOperator::close() { tuples_.clear(); return record_scanner_.close_scan(); }

Tuple *TableScanPhysicalOperator::current_tuple() { return tuples_.back(); }

string TableScanPhysicalOperator::param() const { return table_->name(); }

void TableScanPhysicalOperator::set_predicates(vector<unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC TableScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (unique_ptr<Expression> &expr : predicates_) {
    // append current tuple into parent query tuples
    std::unordered_map<std::string, Tuple *> parent_query_tuples = get_parent_query_tuples();
    std::string table_name = tuple.get_table_name();
    parent_query_tuples[table_name] = &tuple;
    expr->set_parent_query_tuples(parent_query_tuples);

    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}
