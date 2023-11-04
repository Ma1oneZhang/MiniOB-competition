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
#include "sql/parser/value.h"
#include "storage/buffer/page.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "event/sql_debug.h"

using namespace std;
inline bool is_null(char *bit_map, int th) { return (bit_map[th / 8] & (1 << (th % 8))) == 1; }

RC TableScanPhysicalOperator::open(Trx *trx)
{
  record_scanner_ = RecordFileScanner();
  RC rc           = table_->get_record_scanner(record_scanner_, trx, readonly_);
  trx_            = trx;

  // open operators in sub-query
  for (auto &expr : predicates_) {
    if (expr->type() == ExprType::COMPARISON) {
      auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());

      if (comparison_expr->left()->type() == ExprType::SUB_QUERY) {  // this expre contain sub-query
        // restore physical operator
        OperExpr                     *oper_expr   = static_cast<OperExpr *>((comparison_expr->left()).get());
        unique_ptr<PhysicalOperator> &physic_oper = oper_expr->get_physic_oper();

        // operator.open(trx)
        rc = physic_oper->open(trx);
        if (rc != RC::SUCCESS)
          return rc;
      }

      if (comparison_expr->right()->type() == ExprType::SUB_QUERY) {  // this expre contain sub-query
        // restore physical operator
        OperExpr                     *oper_expr   = static_cast<OperExpr *>((comparison_expr->right()).get());
        unique_ptr<PhysicalOperator> &physic_oper = oper_expr->get_physic_oper();

        // operator.open(trx)
        rc = physic_oper->open(trx);
        if (rc != RC::SUCCESS)
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

    bool has_text = false;
    for (int i = 0; i < table_->table_meta().field_metas()->size(); i++) {
      if (table_->table_meta().field_metas()->at(i).type() == TEXTS) {
        has_text = true;
        break;
      }
    }
    if (has_text) {
      std::vector<std::string> texts;
      auto                     t          = current_record_.len();
      auto                     new_record = new char[current_record_.len()];
      memcpy(new_record, current_record_.data(), current_record_.len());
      current_record_.set_data_owner(new_record, current_record_.len());

      for (int i = 0; i < table_->table_meta().field_metas()->size(); i++) {
        auto field = table_->table_meta().field_metas()->at(i);
        if (field.type() == TEXTS) {
          std::string text = "";
          // parse the text from disk manager
          auto bpm          = table_->get_text_buffer_pool();
          auto num_of_page  = (reinterpret_cast<int *>(current_record_.data() + field.offset()));
          auto page_numbers = reinterpret_cast<int *>(current_record_.data() + field.offset() + sizeof(int));
          for (int i = 0; i < *num_of_page; i++) {
            Frame *frame;
            bpm->get_this_page(page_numbers[i], &frame);
            for (int j = 0; j < BP_PAGE_DATA_SIZE; j++) {
              if (frame->page().data[j]) {
                text += frame->page().data[j];
              } else {
                break;
              }
            }
            bpm->unpin_page(frame);
          };
          auto text_address = reinterpret_cast<char **>(page_numbers);
          auto text_data    = new char[text.size()];
          memcpy(text_data, text.c_str(), text.size());
          *num_of_page  = text.size();
          *text_address = text_data;
        }
      }
    }
    // current_record_
    if (rc != RC::SUCCESS) {
      return rc;
    }
    auto tuple = new RowTuple();
    tuple->set_record(current_record_);
    tuple->set_schema(table_, table_->table_meta().field_metas());
    int offset = 0;
    rc         = filter(*tuple, filter_result);
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

RC TableScanPhysicalOperator::close()
{
  tuples_.clear();
  return record_scanner_.close_scan();
}

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
    std::string                              table_name          = tuple.get_table_name();
    std::string                              table_alias         = tuple.get_table()->alias();
    parent_query_tuples[table_name]                              = &tuple;
    parent_query_tuples[table_alias]                             = &tuple;
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
