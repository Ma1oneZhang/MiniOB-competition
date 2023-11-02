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

#include "sql/stmt/create_table_stmt.h"
#include "common/rc.h"
#include "event/sql_debug.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "storage/field/field.h"

RC CreateTableStmt::create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt)
{
  if (create_table.select_node != nullptr) {
    Stmt *temp_stmt = nullptr;
    auto  rc        = create_stmt(db, *create_table.select_node, temp_stmt);
    if (OB_FAIL(rc)) {
      LOG_WARN("parse the select stmt error");
      return rc;
    }
    std::vector<AttrInfoSqlNode> attr_infos;
    auto                         select_stmt = static_cast<SelectStmt *>(temp_stmt);

    if (create_table.attr_infos.size()) {
      if (select_stmt->query_fields().size() != create_table.attr_infos.size()) {
        LOG_WARN("the fields number not equal, exit");
        return RC::INVALID_ARGUMENT;
      }
      for (int i = 0; i < create_table.attr_infos.size(); i++) {
        if (create_table.attr_infos[i].type != select_stmt->query_fields()[i].attr_type()) {
          LOG_WARN("the fields type not match, exit");
          return RC::INVALID_ARGUMENT;
        }
      }
      attr_infos = std::vector<AttrInfoSqlNode>(create_table.attr_infos.begin(), create_table.attr_infos.end());
    } else {
      for (auto &info : select_stmt->query_fields()) {
        // in the competition, the expression must be the number field
        // so we needn't to do something that to get length field
        if (info.is_expr()) {
          // exprssion will be null,so we use null to get it
          AttrInfoSqlNode info_node_ = {
              .type = info.expr()->value_type(), .name = info.expr()->name(), .length = 4, .nullable = true};
          attr_infos.push_back(info_node_);
        } else {
          AttrInfoSqlNode info_node_ = {
              .type     = info.attr_type(),
              .name     = info.field_name(),
              .length   = static_cast<size_t>(info.meta()->len()),
              .nullable = info.meta()->nullable(),
          };
          attr_infos.push_back(info_node_);
        }
      }
    }
    stmt = new CreateTableStmt(create_table.relation_name, attr_infos, static_cast<SelectStmt *>(select_stmt));
  } else {
    stmt = new CreateTableStmt(create_table.relation_name, create_table.attr_infos, nullptr);
  }

  sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}
