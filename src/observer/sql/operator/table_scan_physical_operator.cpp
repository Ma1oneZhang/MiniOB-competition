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
  RC rc = table_->get_record_scanner(record_scanner_, trx, readonly_);
  trx_  = trx;
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

    auto data = new char[current_record_.len()];
    memcpy(data, current_record_.data(), current_record_.len());
    Record scan_result;
    scan_result.set_data_owner(data, current_record_.len());

    auto tuple = new RowTuple();
    tuple->set_record(scan_result);
    tuple->set_schema(table_, table_->table_meta().field_metas());

    rc = filter(*tuple, filter_result);
    if (rc != RC::SUCCESS) {
      delete tuple;
      return rc;
    }

    if (filter_result) {
      tuples_.push_back(tuple);
      LOG_WARN("get a tuple: %s", tuples_.back()->to_string().c_str());
      break;
    } else {
      sql_debug("a tuple is filtered: %s", tuples_.back()->to_string().c_str());
      delete tuple;
      rc = RC::RECORD_EOF;
    }
  }
  return rc;
}

RC TableScanPhysicalOperator::close() { return record_scanner_.close_scan(); }

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
