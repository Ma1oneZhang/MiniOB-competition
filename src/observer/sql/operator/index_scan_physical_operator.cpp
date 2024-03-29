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
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/index_scan_physical_operator.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

IndexScanPhysicalOperator::IndexScanPhysicalOperator(Table *table, Index *index, bool readonly,
    std::vector<ValueExpr *> &left, std::vector<ValueExpr *> &right, bool left_inclusive /*true*/,
    bool right_inclusive /*true*/)
    : table_(table),
      index_(index),
      readonly_(readonly),
      left_inclusive_(left_inclusive),
      right_inclusive_(right_inclusive)
{
  left_length_ = 0, right_length_ = 0;
  for (auto l : left) {
    left_length_ += l->get_value().length();
  }
  for (auto r : right) {
    right_length_ += r->get_value().length();
  }
  left_value_  = new char[left_length_];
  right_value_ = new char[right_length_];
  int offset   = 0;
  for (int i = 0; i < left.size(); i++) {
    // if(index->index_meta().field())
    const auto &l = left[i];
    if (l->get_value().get_isnull()) {
      // magic number 0x7F
      size_t field_length = 0;
      auto   field_name   = index->index_meta().field()[i].c_str();
      field_length        = table->table_meta().field(field_name)->len();
      memset(left_value_ + offset, 0x7F, field_length);
      offset += field_length;
    } else {
      memcpy(left_value_ + offset, l->get_value().data(), l->get_value().length());
      offset += l->get_value().length();
    }
  }
  offset = 0;
  for (int i = 0; i < right.size(); i++) {
    // if(index->index_meta().field())
    const auto &r = right[i];
    if (r->get_value().get_isnull()) {
      // magic number 0x7F
      size_t field_length = 0;
      auto   field_name   = index->index_meta().field()[i].c_str();
      field_length        = table->table_meta().field(field_name)->len();
      memset(right_value_ + offset, 0x7F, field_length);
      offset += field_length;
    } else {
      memcpy(right_value_ + offset, r->get_value().data(), r->get_value().length());
      offset += r->get_value().length();
    }
  }
}

RC IndexScanPhysicalOperator::open(Trx *trx)
{
  if (nullptr == table_ || nullptr == index_) {
    return RC::INTERNAL;
  }

  IndexScanner *index_scanner =
      index_->create_scanner(left_value_, left_length_, left_inclusive_, right_value_, right_length_, right_inclusive_);
  if (nullptr == index_scanner) {
    return RC::INTERNAL;
  }

  record_handler_ = table_->record_handler();
  if (nullptr == record_handler_) {
    LOG_WARN("invalid record handler");
    index_scanner->destroy();
    return RC::INTERNAL;
  }
  index_scanner_ = index_scanner;

  trx_ = trx;
  return RC::SUCCESS;
}

RC IndexScanPhysicalOperator::next()
{
  RID rid;
  RC  rc = RC::SUCCESS;

  if (pos == -1) {
    while (RC::SUCCESS == (rc = index_scanner_->next_entry(&rid))) {
      record_page_handler_.cleanup();
      rc = record_handler_->get_record(record_page_handler_, &rid, readonly_, &current_record_);
      if (rc != RC::SUCCESS) {
        return rc;
      }

      auto tuple = new RowTuple();
      tuple->set_schema(table_, table_->table_meta().field_metas());
      tuple->set_record(current_record_);

      // do filter
      bool filter_result = false;
      rc                 = filter(*tuple, filter_result);
      if (rc != RC::SUCCESS) {
        delete tuple;
        return rc;
      }
      if (!filter_result) {
        delete tuple;
        continue;
      }

      rc = trx_->visit_record(table_, current_record_, readonly_);
      if (rc == RC::RECORD_INVISIBLE) {
        delete tuple;
        continue;
      } else {
        tuples_.push_back(tuple);
      }
    }
  }
  pos++;
  return pos == tuples_.size() ? RC::RECORD_EOF : RC::SUCCESS;
}

RC IndexScanPhysicalOperator::close()
{
  delete right_value_;
  delete left_value_;
  if (index_scanner_ != nullptr)
    index_scanner_->destroy();
  index_scanner_ = nullptr;
  return RC::SUCCESS;
}

Tuple *IndexScanPhysicalOperator::current_tuple() { return tuples_[pos]; }

void IndexScanPhysicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC IndexScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (std::unique_ptr<Expression> &expr : predicates_) {
    auto equal = static_cast<ComparisonExpr *>(expr.get());
    rc         = expr->get_value(tuple, value);
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

std::string IndexScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
