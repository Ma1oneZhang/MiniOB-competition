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
// Created by Wangyunlai on 2023/6/13.
//

#include "sql/executor/create_table_executor.h"

#include "session/session.h"
#include "common/log/log.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "sql/stmt/create_table_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "storage/db/db.h"

RC CreateTableExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_TABLE,
      "create table executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  CreateTableStmt *create_table_stmt = static_cast<CreateTableStmt *>(stmt);

  const int attribute_count = static_cast<int>(create_table_stmt->attr_infos().size());

  const char *table_name = create_table_stmt->table_name().c_str();
  auto        db         = session->get_current_db();
  RC          rc         = db->create_table(table_name, attribute_count, create_table_stmt->attr_infos().data());
  if (create_table_stmt->with_select()) {
    auto  table             = db->find_table(table_name);
    auto &physical_operator = create_table_stmt->get_physical_operator();
    physical_operator->open(nullptr);
    auto sub_rc = RC::RECORD_EOF;

    while (RC::SUCCESS == (sub_rc = physical_operator->next())) {
      auto               tuple = physical_operator->current_tuple();
      std::vector<Value> v;
      for (auto i = 0; i < tuple->cell_num(); i++) {
        Value value;
        auto  rc = tuple->cell_at(i, value);
        v.push_back(value);
      }
      Record record;
      auto   rc = table->make_record(v.size(), v.data(), record);
      table->insert_record(record);
    }
    physical_operator->close();
  }
  return rc;
}