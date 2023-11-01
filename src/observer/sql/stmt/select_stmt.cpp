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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/table/table.h"

void build_aggr_field_name(AggregationType type, std::string &field_name)
{
  switch (type) {
    case AggregationType::MAX: {
      field_name = "MAX(" + field_name + ")";
    } break;
    case AggregationType::MIN: {
      field_name = "MIN(" + field_name + ")";
    } break;
    case AggregationType::COUNT: {
      field_name = "COUNT(" + field_name + ")";
    } break;
    case AggregationType::AVG: {
      field_name = "AVG(" + field_name + ")";
    } break;
    case AggregationType::SUM: {
      field_name = "SUM(" + field_name + ")";
    } break;
    case AggregationType::NONE: {
      LOG_PANIC("WARN_AGGREGATION_TYPE");
    } break;
  }
}

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;
  std::vector<ConditionSqlNode>            conditions = select_sql.conditions;

  // check sql relations
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    auto &table_name = select_sql.relations[i];
    if ("" == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name.c_str());
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    if (std::find(tables.begin(), tables.end(), table) == tables.end()) {
      tables.emplace_back(table);
    }
    table_map[table_name] = table;
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    if (relation_attr.aggregation_type != AggregationType::NONE) {
      // aggregation function
      if (select_sql.orderby.size() != 0) {
        return RC::INVALID_ARGUMENT;
      }
      // check if the relation_attr is valid
      if (common::is_blank(relation_attr.relation_name.c_str()) &&
          0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
        // only count operation support "*" relation
        if (relation_attr.aggregation_type != AggregationType::COUNT) {
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        } else {
          if (tables.size() != 1) {
            return RC::SCHEMA_FIELD_NOT_EXIST;
          }
          query_fields.push_back(Field(*tables.begin(), nullptr, AggregationType::COUNT));
        }
      } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
        const char *table_name = relation_attr.relation_name.c_str();
        const char *field_name = relation_attr.attribute_name.c_str();

        if (0 == strcmp(table_name, "*")) {
          if (0 != strcmp(field_name, "*")) {
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          // only count operation support "*" relation
          if (relation_attr.aggregation_type != AggregationType::COUNT) {
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          } else {
            Field aggr_field;
            aggr_field.set_aggr_type(AggregationType::COUNT);
            aggr_field.set_table(table_map[table_name]);
            query_fields.push_back(aggr_field);
          }
        } else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {
            // only count operation support "*" relation
            if (relation_attr.aggregation_type != AggregationType::COUNT) {
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
            } else {
              Field aggr_field;
              aggr_field.set_table(table);
              aggr_field.set_aggr_type(AggregationType::COUNT);
              query_fields.push_back(aggr_field);
            }
          } else {
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }

            query_fields.push_back(Field(table, field_meta, relation_attr.aggregation_type));
          }
        }
      } else {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table           *table      = *tables.begin();
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        query_fields.push_back(Field(table, field_meta, relation_attr.aggregation_type));
      }
    } else {
      // Have no aggregation function
      // add the join's table to the tables
      for (size_t i = 0; i < select_sql.joinctions.size(); i++) {
        auto &table_name = select_sql.joinctions[i].join_relation;
        if ("" == table_name) {
          LOG_WARN("invalid argument. join relation name is null. index=%d", i);
          return RC::INVALID_ARGUMENT;
        }

        Table *table = db->find_table(table_name.c_str());
        if (nullptr == table) {
          LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name.c_str());
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }

        if (std::find(tables.begin(), tables.end(), table) == tables.end()) {
          tables.emplace_back(table);
        }
        table_map[table_name] = table;
      }
      // check if the relation_attr is valid
      if (common::is_blank(relation_attr.relation_name.c_str()) &&
          0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
        const char *table_name = relation_attr.relation_name.c_str();
        const char *field_name = relation_attr.attribute_name.c_str();

        if (0 == strcmp(table_name, "*")) {
          if (0 != strcmp(field_name, "*")) {
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          for (Table *table : tables) {
            wildcard_fields(table, query_fields);
          }
        } else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {
            wildcard_fields(table, query_fields);
          } else {
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }

            query_fields.push_back(Field(table, field_meta));
          }
        }
      } else {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table           *table      = *tables.begin();
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        query_fields.push_back(Field(table, field_meta));
      }
    }
  }

  // append tables in parent query
  for (const auto& pair : select_sql.parent_query_tables) {
    if(table_map.count(pair.first) == 0) {
      table_map[pair.first] = pair.second;
    }
  }
  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = *tables.begin();
  }

  // create join conditions in `join` statement
  for (size_t i = 0; i < select_sql.joinctions.size(); i++) {
    std::vector<ConditionSqlNode> const &tmp_vec_condi = select_sql.joinctions[i].join_conditions;
    for (auto &j : tmp_vec_condi)
      conditions.emplace_back(j);
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, default_table, &table_map, conditions.data(), static_cast<int>(conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }
  // create order by stmt in 'ordey_by' statement
  OrderByStmt *order_by_stmt = nullptr;
  rc                         = OrderByStmt::create(db, default_table, &table_map, &select_sql.orderby, order_by_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct order by stmt");
    return rc;
  }

  // check if have no group by, then only allowed aggregation function
  if (select_sql.groupby.size() == 0) {
    bool has_aggr = false;
    for (size_t i = 0; i < select_sql.attributes.size(); i++) {
      if (select_sql.attributes[i].aggregation_type != AggregationType::NONE) {
        has_aggr = true;
      }
    }
    if (has_aggr) {
      for (size_t i = 0; i < select_sql.attributes.size(); i++) {
        if (select_sql.attributes[i].aggregation_type == AggregationType::NONE) {
          LOG_WARN("invalid group by condition");
          return RC::INVALID_ARGUMENT;
        }
      }
    }
  }

  // check the group by condition is valid
  std::vector<Field> groupby;
  if (select_sql.groupby.size() != 0) {
    for (size_t i = 0; i < select_sql.groupby.size(); i++) {
      if (select_sql.groupby[i].aggregation_type != AggregationType::NONE) {
        LOG_WARN("invalid group by condition");
        return RC::INVALID_ARGUMENT;
      }
      // check the group by is exist in the query fields
      bool is_exist = false;
      for (size_t j = 0; j < query_fields.size(); j++) {
        // check the attr name is exist in the query fields
        if ((select_sql.groupby[i].relation_name == query_fields[j].table()->name() ||
                select_sql.groupby[i].relation_name == "") &&
            select_sql.groupby[i].attribute_name == query_fields[j].field_name()) {
          is_exist = true;
          break;
        }
      }
      if (!is_exist) {
        LOG_WARN("invalid group by condition");
        return RC::INVALID_ARGUMENT;
      }
    }
  }
  // add to group by vector
  for (size_t i = 0; i < select_sql.groupby.size(); i++) {
    for (size_t j = 0; j < query_fields.size(); j++) {
      // add table name to the group field
      if (select_sql.groupby[i].attribute_name == query_fields[j].field_name()) {
        groupby.push_back(query_fields[j]);
        break;
      }
    }
  }

  // check the having condition is existed with group by
  if (select_sql.groupby.size() == 0 && select_sql.having.size() != 0) {
    LOG_WARN("invalid having condition");
    return RC::INVALID_ARGUMENT;
  }

  // check the having condition is valid
  if (select_sql.having.size() != 0) {
    for (size_t i = 0; i < select_sql.having.size(); i++) {
      if (select_sql.having[i].left_attr.aggregation_type == AggregationType::NONE) {
        LOG_WARN("invalid having condition");
        return RC::INVALID_ARGUMENT;
      }
      // // check the having is exist in the query fields
      // bool is_exist = false;
      // for (size_t j = 0; j < query_fields.size(); j++) {
      //   // check the attr name is exist in the query fields
      //   auto attr_name = select_sql.having[i].left_attr.attribute_name;
      //   build_aggr_field_name(select_sql.having[i].left_attr.aggregation_type, attr_name);
      //   if ((select_sql.having[i].left_attr.relation_name == query_fields[j].table()->name() ||
      //           select_sql.having[i].left_attr.relation_name == "") &&
      //       attr_name == query_fields[j].field_name()) {
      //     is_exist = true;
      //     break;
      //   }
      // }
      // if (!is_exist) {
      //   LOG_WARN("invalid having condition");
      //   return RC::INVALID_ARGUMENT;
      // }
    }
  }
  // create filter stmt for having
  FilterStmt *having_stmt = nullptr;
  if (!select_sql.having.empty()) {
    rc = FilterStmt::create(db,
        default_table,
        &table_map,
        select_sql.having.data(),
        static_cast<int>(select_sql.having.size()),
        having_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct having stmt");
      return rc;
    }
  }

  // everything alright
  SelectStmt        *select_stmt = new SelectStmt();
  std::vector<Field> having;
  if (having_stmt) {
    for (auto having_field : having_stmt->filter_units()) {
      if (having_field->left().is_attr == 1) {
        having.push_back(having_field->left().field);
      }
      if (having_field->right().is_attr == 1) {
        having.push_back(having_field->right().field);
      }
    }
  }
  select_stmt->tables_ = std::vector<Table *>(tables.begin(), tables.end());
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->having_stmt_   = having_stmt;
  select_stmt->filter_stmt_   = filter_stmt;
  select_stmt->order_by_stmt_ = order_by_stmt;
  select_stmt->group_by_       = groupby;
  select_stmt->having_         = std::move(having);
  stmt                        = select_stmt;

  return RC::SUCCESS;
}
