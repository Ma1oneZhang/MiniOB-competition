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

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  if (condition_num > 0) {
    tmp_stmt->link_type_ = conditions[0].link_type;
  }

  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc                      = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;
  if (condition.left_is_attr == 4) {
    if (condition.left_expr->type() == ExprType::FIELD) {
      auto field_expr        = static_cast<FieldExpr *>(condition.left_expr);
      condition.left_attr    = field_expr->get_sql_node();
      condition.left_is_attr = 1;
    } else if (condition.left_expr->type() == ExprType::VALUE) {
      auto value_expr = static_cast<ValueExpr *>(condition.left_expr);
      value_expr->get_value(condition.left_value);
      condition.left_is_attr = 0;
    }
  }
  if (condition.right_is_attr == 4) {
    if (condition.right_expr->type() == ExprType::FIELD) {
      auto field_expr         = static_cast<FieldExpr *>(condition.right_expr);
      condition.right_attr    = field_expr->get_sql_node();
      condition.right_is_attr = 1;
    } else if (condition.right_expr->type() == ExprType::VALUE) {
      auto value_expr         = static_cast<ValueExpr *>(condition.right_expr);
      condition.right_value   = value_expr->get_value();
      condition.right_is_attr = 0;
    }
  }
  if (condition.left_is_attr == 1) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    FilterObj        filter_obj;
    if (condition.left_attr.aggregation_type == AggregationType::COUNT && condition.left_attr.attribute_name == "*") {
      filter_obj.init_attr(Field(default_table, nullptr, condition.left_attr.aggregation_type));
      filter_unit->set_left(filter_obj);
    } else {
      rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      if ((comp == LIKE_OP || comp == NOT_LIKE_OP) && field->type() != AttrType::CHARS) {
        return RC::INVALID_ARGUMENT;
      }
      if (field->type() == AttrType::DATES &&
          (condition.comp != CompOp::IS_NOT_NULL && condition.comp != CompOp::IS_NULL)) {
        auto value = condition.right_value;
        if (!value.get_isnull()) {
          auto status = value.match_field_type(AttrType::DATES);
          if (!status) {
            return RC::INVALID_ARGUMENT;
          }
        }
      }
      filter_obj.init_attr(Field(table, field, condition.left_attr.aggregation_type));
      filter_unit->set_left(filter_obj);
    }

  } else if (condition.left_is_attr == 0) {
    FilterObj filter_obj;
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  } else if (condition.left_is_attr == 2) {
    // append tables to sub-qeury
    condition.left_sub_query->selection.parent_query_tables = *tables;

    Stmt *stmt = nullptr;
    rc         = Stmt::create_stmt(db, *condition.left_sub_query, stmt);

    FilterObj filter_obj;
    filter_obj.init_stmt(stmt);
    filter_unit->set_left(filter_obj);
  } else if (condition.left_is_attr == 3) {
    FilterObj filter_obj;
    filter_obj.init_valuelist(condition.left_value_list);
    filter_unit->set_left(filter_obj);
  } else if (condition.left_is_attr == 4) {
    FilterObj filter_obj;
    filter_obj.init_expr(condition.left_expr);
    filter_unit->set_left(filter_obj);
  }

  if (condition.right_is_attr == 1) {  // the right is attr
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    if (condition.right_attr.aggregation_type == AggregationType::COUNT && condition.right_attr.attribute_name == "*") {
      FilterObj filter_obj;
      filter_obj.init_attr(Field(default_table, nullptr, condition.left_attr.aggregation_type));
      filter_unit->set_right(filter_obj);
    } else {
      rc = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      FilterObj filter_obj;
      filter_obj.init_attr(Field(table, field));
      filter_unit->set_right(filter_obj);
    }
  } else if (condition.right_is_attr == 0) {  // the right is value
    FilterObj filter_obj;
    filter_obj.init_value(condition.right_value);
    filter_unit->set_right(filter_obj);
  } else if (condition.right_is_attr == 2) {
    // append tables to sub-qeury
    condition.right_sub_query->selection.parent_query_tables = *tables;

    Stmt *stmt = nullptr;
    rc         = Stmt::create_stmt(db, *condition.right_sub_query, stmt);

    FilterObj filter_obj;
    filter_obj.init_stmt(stmt);
    filter_unit->set_right(filter_obj);
  } else if (condition.right_is_attr == 3) {
    FilterObj filter_obj;
    filter_obj.init_valuelist(condition.right_value_list);
    filter_unit->set_right(filter_obj);
  } else if (condition.right_is_attr == 4) {
    FilterObj filter_obj;
    filter_obj.init_expr(condition.right_expr);
    filter_unit->set_right(filter_obj);
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}
