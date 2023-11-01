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

#include <vector>
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"

#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

struct FilterObj
{
  int           is_attr;  // 0: value, 1: attr, 2: sub_query, 3: value list 4: expression
  Field         field;
  Value         value;
  Stmt         *sub_query;
  vector<Value> value_list;
  Expression   *expr_ = nullptr;
  void          init_attr(const Field &field)
  {
    is_attr     = 1;
    this->field = field;
  }

  void init_value(const Value &value)
  {
    is_attr     = 0;
    this->value = value;
  }

  void init_stmt(Stmt *stmt)
  {
    is_attr         = 2;
    this->sub_query = stmt;
  }

  void init_valuelist(vector<Value> vl)
  {
    is_attr          = 3;
    this->value_list = vl;
  }
  void init_expr(Expression *expr)
  {
    is_attr = 4;
    expr_   = expr;
  }
};

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  void set_left(const FilterObj &obj) { left_ = obj; }
  void set_right(const FilterObj &obj) { right_ = obj; }

  const FilterObj &left() const { return left_; }
  const FilterObj &right() const { return right_; }

private:
  CompOp    comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const { return filter_units_; }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      ConditionSqlNode &condition, FilterUnit *&filter_unit);

  int get_link_type() { return link_type_; }

private:
  std::vector<FilterUnit *> filter_units_;
  int                       link_type_ = 0;  // 0: AND, 1: OR
};
