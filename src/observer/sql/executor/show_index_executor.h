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
// Created by Wangyunlai on 2023/6/14.
//

#pragma once

#include "common/rc.h"
#include "sql/operator/string_list_physical_operator.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/executor/sql_result.h"
#include "session/session.h"
#include "sql/stmt/show_index_stmt.h"
#include "storage/db/db.h"
#include "storage/index/index.h"
#include <cctype>

/**
 * @brief 显示所有表的执行器
 * @ingroup Executor
 * @note 与CreateIndex类似，不处理并发
 */
class ShowIndexExecutor
{
public:
  ShowIndexExecutor()          = default;
  virtual ~ShowIndexExecutor() = default;

  RC execute(SQLStageEvent *sql_event)
  {
    SqlResult     *sql_result    = sql_event->session_event()->sql_result();
    SessionEvent  *session_event = sql_event->session_event();
    ShowIndexStmt *stmt          = static_cast<ShowIndexStmt *>(sql_event->stmt());

    Db    *db    = session_event->session()->get_current_db();
    Table *table = db->find_table(stmt->table_name());
    // we have checked the table exists.
    std::vector<std::string> all_tables;
    db->all_tables(all_tables);

    TupleSchema tuple_schema;
    tuple_schema.append_cell(TupleCellSpec("", "Table", "Table"));
    tuple_schema.append_cell(TupleCellSpec("", "Non_unique", "Non_unique"));
    tuple_schema.append_cell(TupleCellSpec("", "Key_name", "Key_name"));
    tuple_schema.append_cell(TupleCellSpec("", "Seq_in_index", "Seq_in_index"));
    tuple_schema.append_cell(TupleCellSpec("", "Column_name", "Column_name"));
    sql_result->set_tuple_schema(tuple_schema);

    auto oper          = new StringListPhysicalOperator;
    auto to_upper_case = [](string str) {
      std::transform(str.begin(), str.end(), str.begin(), ::toupper);
      return str;
    };
    for (int i = 0; i < table->table_meta().index_num(); i++) {
      auto index_meta = table->table_meta().index(i);
      oper->append({to_upper_case(std::string(table->table_meta().name())),  // Table
          std::to_string(1),                                                 // Non_unique
          to_upper_case(index_meta->name()),                                 // Key_name
          std::to_string(i + 1),                                             // Seq_in_index
          to_upper_case(std::string(index_meta->field()))});                 // Column_name
    }

    sql_result->set_operator(std::unique_ptr<PhysicalOperator>(oper));
    return RC::SUCCESS;
  }
};