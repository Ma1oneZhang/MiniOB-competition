#pragma once

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"

class DropTableStmt : public Stmt
{
public:
  DropTableStmt(const char *table_name);
  virtual ~DropTableStmt() = default;
  StmtType    type() const override { return StmtType::DROP_TABLE; }
  const char *table_name() { return table_name_; }

  static RC create(Db *db, const DropTableSqlNode &sql, Stmt *&stmt);

private:
  const char *table_name_;
};