/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <ctype.h>
#include <cmath>

InsertStmt::InsertStmt(Table *table, const std::vector<std::vector<Value>> *values) : table_(table), values_(values) {}

RC InsertStmt::create(Db *db, InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  std::vector<std::vector<Value>> *values = &inserts.values;
  for (auto &value : inserts.values) {
    const int        value_num  = static_cast<int>(value.size());
    const TableMeta &table_meta = table->table_meta();
    const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
    if (field_num != value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }
    // check fields type
    const int sys_field_num = table_meta.sys_field_num();
    for (auto &tuple : *values) {
      for (int i = 0; i < value_num; i++) {
        const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
        const AttrType   field_type = field_meta->type();
        const AttrType   value_type = tuple[i].attr_type();

        // types of field and value match, continue to next field.
        if (value_type == field_type){
          continue;
        }

        // addree the case when the value is null
        if(tuple[i].get_isnull()) {
          if(field_meta->nullable()) 
            continue;
          else
            return RC::FIELD_COULD_NOT_BE_NULL;
        }

        if (!tuple[i].match_field_type(field_type)) {
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
                table_name, field_meta->name(), field_type, value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }
    }
  }

  // everything alright
  stmt = new InsertStmt(table, values);
  return RC::SUCCESS;
}
