#include "drop_table_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"


using common::is_blank;

DropTableStmt::DropTableStmt(const char *str) { this->table_name_ = str; }

RC DropTableStmt::create(Db *db, const DropTableSqlNode &sql, Stmt *&stmt)
{
  const char *table_name = sql.relation_name.c_str();
  if (is_blank(table_name)) {
    LOG_WARN("invalid argument. db=%p, table_name=%s", db, table_name);
    return RC::INVALID_ARGUMENT;
  }
  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("No such table. db=%p, table_name=%s", db, table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  stmt = new DropTableStmt(table_name);
  return RC::SUCCESS;
}