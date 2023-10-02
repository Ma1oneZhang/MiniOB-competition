#include "drop_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

using common::is_blank;

DropIndexStmt::DropIndexStmt(const char *table_name, const char *index_name)
{
  this->table_name_ = table_name;
  this->index_name_ = index_name;
}

RC DropIndexStmt::create(Db *db, const DropIndexSqlNode &sql, Stmt *&stmt)
{
  const char *table_name = sql.relation_name.c_str();
  const char *index_name = sql.index_name.c_str();
  if (is_blank(table_name)) {
    LOG_WARN("invalid argument. db=%p, table_name=%s", db, table_name);
    return RC::INVALID_ARGUMENT;
  }
  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("No such table. db=%p, table_name=%s", db, table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  auto index = table->find_index(index_name);
  if (index == nullptr) {
    LOG_WARN("No such table. db=%p, table_name=%s", db, table_name);
    return RC::SCHEMA_INDEX_NOT_EXIST;
  }
  stmt = new DropIndexStmt(table_name, index_name);
  return RC::SUCCESS;
}