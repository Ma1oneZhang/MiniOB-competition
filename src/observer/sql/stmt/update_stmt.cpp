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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <vector>

UpdateStmt::UpdateStmt(
    Table *table, std::vector<LazyValue> &&values, FilterStmt *filter, std::vector<std::string> &&attribute_names)
    : table_(table), filter_(filter), attribute_names_(attribute_names)
{
  values_.swap(values);
  value_amount_ = values_.size();
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  auto table = db->find_table(update.relation_name.c_str());
  if (table == nullptr) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  auto                     fields = table->table_meta().field_metas();
  std::vector<LazyValue>   values;
  std::vector<std::string> field_names;
  for (size_t i = 0; i < update.attribute_name.size(); i++) {
    auto &field = update.attribute_name[i];
    auto &value = update.value[i];
    bool  match = false;
    for (auto iter = fields->begin(); iter != fields->end(); iter++) {
      if (field == iter->name()) {
        if (value.is_stmt) {
          match = true;
          if (value.stmt->flag != SCF_SELECT) {
            return RC::INVALID_ARGUMENT;
          }
          Stmt *stmt = nullptr;
          auto  rc   = Stmt::create_stmt(db, *value.stmt, stmt);
          if (rc != RC::SUCCESS) {
            stmt = nullptr;
            return rc;
          }
          // check if return multi-field
          auto        select_stmt  = static_cast<SelectStmt *>(stmt);
          const auto &query_fields = select_stmt->query_fields();
          if (query_fields.size() != 1) {
            LOG_WARN("query return more than one field");
            return RC::MULTI_COL_RETURN;
          }
          // check the query field is matchi
          const auto &field = query_fields.front();
          if (!Value::check_match_field_type(field.attr_type(), iter->type())) {
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          values.push_back(select_stmt);
        } else if (value.value.get_isnull()) {
          match  = true;
          auto i = value.value;
          values.emplace_back(i);
          break;
        } else if (Value::check_match_field_type(value.value.attr_type(), iter->type())) {
          // we only need match one of field
          auto i = value.value;
          values.emplace_back(i);
          match = true;
          break;
        } else {
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }
    }
    if (!match) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_names.push_back(update.attribute_name[i]);
  }
  std::vector<Table *> tables = {table};
  for (auto &i : update.conditions) {
    if (i.left_is_attr == 4) {
      auto rc = i.left_expr->set_table_name(tables);
      if (OB_FAIL(rc)) {
        return rc;
      }
    }
    if (i.right_is_attr == 4) {
      auto rc = i.right_expr->set_table_name(tables);
      if (OB_FAIL(rc)) {
        return rc;
      }
    }
  }
  FilterStmt *filter = nullptr;
  if (update.conditions.size() != 0) {
    auto rc = FilterStmt::create(
        db, table, nullptr, const_cast<ConditionSqlNode *>(update.conditions.data()), update.conditions.size(), filter);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  stmt = new UpdateStmt(table, std::move(values), filter, std::move(field_names));
  return RC::SUCCESS;
}
