#pragma once

#include "sql/stmt/stmt.h"
#include "storage/db/db.h"

class ShowIndexStmt : public Stmt
{
public:
  ShowIndexStmt(const char *table_name) : table_name_(table_name){};
  virtual ~ShowIndexStmt() = default;

  StmtType type() const override { return StmtType::SHOW_INDEX; }

  static RC create(Db *db, ShowIndexSqlNode &sql_node, Stmt *&stmt)
  {
    auto table_name = sql_node.relation_name.c_str();
    if (!db->find_table(table_name)) {
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    stmt = new ShowIndexStmt(table_name);
    return RC::SUCCESS;
  }

  const char *table_name() { return table_name_; }

private:
  const char *table_name_ = nullptr;
};