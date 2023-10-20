#include "sql/stmt/order_by_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"

static RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    OrderBySqlNode &attr, Table *&table, const FieldMeta *&field)
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
  attr.relation_name = table->name();

  return RC::SUCCESS;
}

RC OrderByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const std::vector<OrderBySqlNode> *units, OrderByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  if (units->size() == 0) {
    // return with nullptr
    return RC::SUCCESS;
  }
  OrderByStmt *tmp_stmt = new OrderByStmt;
  for (size_t i = 0; i < units->size(); i++) {
    auto            &unit  = const_cast<OrderBySqlNode &>(units->at(i));
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, unit, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
  }
  tmp_stmt->order_by_units = const_cast<std::vector<OrderBySqlNode> *>(units);
  stmt = tmp_stmt;
  return RC::SUCCESS;
}
