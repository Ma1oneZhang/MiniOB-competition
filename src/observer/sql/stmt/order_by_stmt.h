#pragma once

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"

#include <unordered_map>

class Table;

class OrderByStmt : public Stmt
{
public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const std::vector<OrderBySqlNode> *order_by_units, OrderByStmt *&stmt);
  virtual ~OrderByStmt() = default;

  StmtType type() const override { return StmtType::ORDER_BY; }

  std::vector<OrderBySqlNode> *get_order_by_units() const { return this->order_by_units; }

private:
  std::vector<OrderBySqlNode> *order_by_units = nullptr;
};
