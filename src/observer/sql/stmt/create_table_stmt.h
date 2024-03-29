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

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateTableStmt : public Stmt
{
public:
  CreateTableStmt(
      const std::string &table_name, const std::vector<AttrInfoSqlNode> &attr_infos, SelectStmt *select_stmt)
      : table_name_(table_name), attr_infos_(attr_infos), select_stmt_(select_stmt)
  {}
  virtual ~CreateTableStmt() = default;

  StmtType type() const override { return StmtType::CREATE_TABLE; }

  const std::string                  &table_name() const { return table_name_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }

  static RC create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt);
  bool      with_select() const { return select_stmt_ != nullptr; }

  std::unique_ptr<LogicalOperator>  &get_logical_operator() { return logical_operator_; }
  std::unique_ptr<PhysicalOperator> &get_physical_operator() { return physical_operator_; }

  SelectStmt *get_select_stmt() { return select_stmt_; }

private:
  std::string                       table_name_;
  std::vector<AttrInfoSqlNode>      attr_infos_;
  std::unique_ptr<LogicalOperator>  logical_operator_;
  std::unique_ptr<PhysicalOperator> physical_operator_;
  SelectStmt                       *select_stmt_ = nullptr;
};