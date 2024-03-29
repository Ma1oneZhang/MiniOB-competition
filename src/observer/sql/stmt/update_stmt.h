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

#pragma once

#include "common/rc.h"
#include "sql/parser/lazy_value.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"

class Table;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  // UpdateStmt() = default;
  UpdateStmt(
      Table *table, std::vector<LazyValue> &&values, FilterStmt *filter, std::vector<std::string> &&attribute_names_);
  ~UpdateStmt() override = default;

  virtual StmtType type() const override { return StmtType::UPDATE; }

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table                    *table() const { return table_; }
  std::vector<LazyValue>   *values() { return &values_; }
  LazyValue                &value_at(size_t i) { return values_[i]; }
  int                       value_amount() const { return value_amount_; }
  const char               *attribute_name(size_t i) { return attribute_names_.at(i).c_str(); }
  std::vector<std::string> *attribute_names() { return &attribute_names_; }
  FilterStmt               *filter() const { return filter_; }

private:
  Table                   *table_           = nullptr;
  std::vector<std::string> attribute_names_ = {};
  FilterStmt              *filter_          = nullptr;
  std::vector<LazyValue>   values_          = {};
  int                      value_amount_    = 0;
};
