#pragma once
#include "sql/stmt/stmt.h"
class DropIndexStmt : public Stmt
{
public:
  DropIndexStmt(const char *table_name, const char *index_name);
  virtual ~DropIndexStmt() = default;
  StmtType    type() const override { return StmtType::DROP_INDEX; }
  const char *table_name() { return table_name_; }
  const char *index_name() { return index_name_; }

  static RC create(Db *db, const DropIndexSqlNode &sql, Stmt *&stmt);

private:
  const char *table_name_;
  const char *index_name_;
};