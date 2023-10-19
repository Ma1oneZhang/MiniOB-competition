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
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <vector>

UpdateStmt::UpdateStmt(
    Table *table, Value *values, FilterStmt *filter, std::vector<std::string> *attribute_names, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount), filter_(filter), attribute_names_(attribute_names)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  // TODO
  auto table = db->find_table(update.relation_name.c_str());
  if (table == nullptr) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  auto fields = table->table_meta().field_metas();
  for (size_t i = 1; i < update.attribute_name.size(); i++) {
    auto &field = update.attribute_name[i];
    auto &value = update.value[i];
    bool  match = false;
    for (auto iter = fields->begin(); iter != fields->end(); iter++) {
      if (iter->name() == field) {
        if (iter->type() == value.attr_type()) {
          // we only need match one of field
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
  }
  FilterStmt *filter = nullptr;
  if (update.conditions.size() != 0) {
    FilterStmt::create(db, table, nullptr, update.conditions.data(), update.conditions.size(), filter);
  }
  stmt = new UpdateStmt(table,
      const_cast<Value *>(update.value.data()),
      filter,
      const_cast<std::vector<std::string> *>(&update.attribute_name),
      update.value.size());
  return RC::SUCCESS;
}
