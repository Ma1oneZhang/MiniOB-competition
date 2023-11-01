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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <string.h>
#include <memory>
#include <string>

#include "sql/parser/parse_defs.h"
#include "storage/field/field.h"
#include "sql/parser/value.h"
#include "common/log/log.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/physical_operator.h"

using namespace std;

class LogicalOperator;
// class PhysicalOperator;

class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType
{
  NONE,
  STAR,         ///< 星号，表示所有字段
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  SUB_QUERY,    ///< 子查询
  VALUELIST     ///< 多个常量值
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression
{
public:
  Expression()          = default;
  virtual ~Expression() = default;

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLENMENT; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string                 name() const { return name_; }
  virtual void                        set_name(std::string name) { name_ = name; }
  virtual std::vector<RelAttrSqlNode> get_rel_attr_sql_node() { return {}; }

  std::unordered_map<std::string, Tuple *> get_parent_query_tuples() { return parent_query_tuples_; };
  RC set_parent_query_tuples(unordered_map<std::string, Tuple *> parent_query_tuples)
  {
    parent_query_tuples_ = parent_query_tuples;
    return RC::SUCCESS;
  }

  virtual RC set_table_name(std::vector<Table *> &) { return RC::SUCCESS; }

private:
  std::string                              name_;
  std::unordered_map<std::string, Tuple *> parent_query_tuples_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Field &field) : field_(field) {}
  FieldExpr(RelAttrSqlNode rel_attr_sql_node) : sql_node_(rel_attr_sql_node) {}

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }

  const char                         *field_name() const { return field_.field_name(); }
  virtual std::vector<RelAttrSqlNode> get_rel_attr_sql_node() override { return {sql_node_}; }

  RC              get_value(const Tuple &tuple, Value &value) override;
  RelAttrSqlNode &get_sql_node() { return sql_node_; }
  virtual RC      set_table_name(std::vector<Table *> &query_tables) override
  {
    if (sql_node_.relation_name != "") {
      for (auto table : query_tables) {
        if (table->name() == sql_node_.relation_name) {
          field_ = Field(table, table->table_meta().field(sql_node_.attribute_name.c_str()));
          return RC::SUCCESS;
        }
      }
    } else {
      for (auto table : query_tables) {
        if (table->table_meta().field(sql_node_.attribute_name.c_str())) {
          field_ = Field(table, table->table_meta().field(sql_node_.attribute_name.c_str()));
          return RC::SUCCESS;
        }
      }
    }
    return RC::NOTFOUND;
  }

private:
  Field          field_;
  RelAttrSqlNode sql_node_;
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) override;
  RC try_get_value(Value &value) const override
  {
    value = value_;
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

private:
  Value value_;
};

class ValueListExpr : public Expression
{
public:
  ValueListExpr() = default;
  explicit ValueListExpr(vector<Value> vl) : value_list_(vl) {}

  virtual ~ValueListExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) override { return RC::SUCCESS; }

  RC try_get_value(Value &value) const override { return RC::SUCCESS; }

  ExprType type() const override { return ExprType::VALUELIST; }

  AttrType value_type() const override { return value_list_[0].attr_type(); }

  vector<Value> &get_valuelist() { return value_list_; }

private:
  vector<Value> value_list_;
};

/**
 * @brief 子查询表达式
 * @ingroup Expression
 */
class OperExpr : public Expression
{
public:
  OperExpr() = default;
  OperExpr(unique_ptr<LogicalOperator> &logic_oper)
  {
    logic_oper_ = std::move(logic_oper);
    set_name("Sub-qeury");
  }

  virtual ~OperExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) override;

  RC try_get_value(Value &value) const override { return RC::SUCCESS; }

  ExprType type() const override { return ExprType::SUB_QUERY; }

  AttrType value_type() const override { return AttrType::UNDEFINED; }

  unique_ptr<LogicalOperator> &get_logic_oper() { return logic_oper_; }

  void set_physic_oper(unique_ptr<PhysicalOperator> &physic_oper) { physic_oper_ = std::move(physic_oper); }
  unique_ptr<PhysicalOperator> &get_physic_oper() { return physic_oper_; }

  RC catch_subquery_results();

  std::vector<Value> &get_subquery_results() { return subquery_results; }

private:
  unique_ptr<LogicalOperator>  logic_oper_;
  unique_ptr<PhysicalOperator> physic_oper_;
  std::vector<Value>           subquery_results;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }
  RC       get_value(const Tuple &tuple, Value &value) override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;      ///< 从这个表达式转换
  AttrType                    cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }

  RC get_value(const Tuple &tuple, Value &value) override;

  AttrType value_type() const override { return BOOLEANS; }

  CompOp comp() const { return comp_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

  RC compare_sub_query(const Value &left, const Value &right, bool &value);

  RC compare_valuelist(const Value &left, const Value &right, bool &value) const;

  RC like_operation(const Value &left, const Value &right, bool &value, bool do_like) const;
  virtual std::vector<RelAttrSqlNode> get_rel_attr_sql_node() override
  {
    auto l = left_->get_rel_attr_sql_node();
    auto r = right_->get_rel_attr_sql_node();
    l.insert(l.end(), r.begin(), r.end());
    return r;
  };

  virtual RC set_table_name(std::vector<Table *> &query_tables) override
  {
    auto rc = left_->set_table_name(query_tables);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    rc = right_->set_table_name(query_tables);
    return rc;
  }

private:
  CompOp                      comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression
{
public:
  enum class Type
  {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

  virtual std::vector<RelAttrSqlNode> get_rel_attr_sql_node() override
  {
    std::vector<RelAttrSqlNode> sql_nodes;
    for (auto &expr : children_) {
      auto child_field = expr->get_rel_attr_sql_node();
      sql_nodes.insert(sql_nodes.end(), child_field.begin(), child_field.end());
    }
    return sql_nodes;
  }
  virtual RC set_table_name(std::vector<Table *> &query_tables) override
  {
    for (auto &expr : children_) {
      auto rc = expr->set_table_name(query_tables);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    return RC::SUCCESS;
  }

private:
  Type                                     conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression
{
public:
  enum class Type
  {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) override;
  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression>        &left() { return left_; }
  std::unique_ptr<Expression>        &right() { return right_; }
  virtual std::vector<RelAttrSqlNode> get_rel_attr_sql_node() override
  {
    auto l = left_->get_rel_attr_sql_node();
    auto r = right_->get_rel_attr_sql_node();
    l.insert(l.end(), r.begin(), r.end());
    return r;
  };
  virtual RC set_table_name(std::vector<Table *> &query_tables) override
  {
    auto rc = left_->set_table_name(query_tables);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    rc = right_->set_table_name(query_tables);
    return rc;
  }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

private:
  Type                        arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};