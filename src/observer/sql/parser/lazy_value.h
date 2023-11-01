#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/stmt/select_stmt.h"

class LazyValue
{
public:
  LazyValue(SelectStmt *stmt) { stmt_ = stmt; };
  LazyValue(Value &value)
  {
    execution_result_ = RC::SUCCESS;
    is_executed_      = true;
    value_            = value;
  };

  std::unique_ptr<PhysicalOperator> &get_physical_operator() { return physical_operator_; }
  void                               set_physical_operator(PhysicalOperator *physical_operator)
  {
    this->physical_operator_ = std::unique_ptr<PhysicalOperator>(physical_operator);
  }

  std::unique_ptr<LogicalOperator> &get_logical_operator() { return logical_operator_; }
  void                              set_logical_operator(LogicalOperator *logical_operator)
  {
    this->logical_operator_ = std::unique_ptr<LogicalOperator>(logical_operator);
  }

  bool is_executed() const { return is_executed_; }

  SelectStmt *get_select_stmt() { return stmt_; }
  RC          try_get_value(Value &result)
  {
    if (!is_executed_) {
      lazy_execution();
    }
    if (execution_result_ != RC::SUCCESS) {
      return execution_result_;
    }
    result = value_;
    return RC::SUCCESS;
  }

private:
  // lazy execution
  void lazy_execution();

  RC                                execution_result_;
  bool                              is_executed_ = false;
  Value                             value_{};
  SelectStmt                       *stmt_              = nullptr;
  std::unique_ptr<PhysicalOperator> physical_operator_ = nullptr;
  std::unique_ptr<LogicalOperator>  logical_operator_  = nullptr;
};