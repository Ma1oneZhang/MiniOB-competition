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

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include <regex>

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value)
{
  RC rc = tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);

  if (rc == RC::NOTFOUND) {
    for (auto &pair : get_parent_query_tuples()) {
      rc = pair.second->find_cell(TupleCellSpec(table_name(), field_name()), value);
      if (rc == RC::SUCCESS) {
        break;
      }
    }
  }

  return rc;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value)
{
  value = value_;
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell)
{
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const
{
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC rc = RC::SUCCESS;
  switch (comp_) {
    case CompOp::LIKE_OP:
    case CompOp::NOT_LIKE_OP: {
      // DO like operation
      return like_operation(left, right, result, comp_ == CompOp::LIKE_OP);
    } break;
    case CompOp::IS_NULL: {
      result = left.get_isnull();
      return rc;
    } break;
    case CompOp::IS_NOT_NULL: {
      result = !(left.get_isnull());
      return rc;
    } break;
    default: break;
  }
  if (left.get_isnull() | right.get_isnull()) {
    result = false;
    return rc;
  }

  int cmp_result = left.compare(right);
  result         = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    case IN_OP: {
      result = (0 == cmp_result);
    } break;
    case NOT_IN_OP: {
      result = (0 == cmp_result);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::compare_sub_query(const Value &left, const Value &right, bool &result)
{
  RC    rc;
  Value left_value;
  Value right_value;

  if (left_->type() == ExprType::SUB_QUERY & right_->type() == ExprType::SUB_QUERY) {
    OperExpr *loper = dynamic_cast<OperExpr *>(left_.get());
    rc              = loper->catch_subquery_results();
    if (rc != RC::SUCCESS)
      return rc;

    OperExpr *roper = dynamic_cast<OperExpr *>(right_.get());
    rc              = roper->catch_subquery_results();
    if (rc != RC::SUCCESS)
      return rc;

    std::vector<Value> &left_subquery_results  = loper->get_subquery_results();
    std::vector<Value> &right_subquery_results = roper->get_subquery_results();
    switch (comp_) {
      case CompOp::IN_OP: {
        int left_row_count = left_subquery_results.size();
        if (left_row_count > 1) {
          return RC::SUBQUERY_TOO_MANY_ROWS;
        }
        left_value = left_subquery_results[0];

        result = false;
        for (int i = 0; i < right_subquery_results.size(); i++) {
          right_value     = right_subquery_results[i];
          bool bool_value = false;
          rc              = compare_value(left_value, right_value, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = true;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      } break;
      case CompOp::NOT_IN_OP: {
        int left_row_count = left_subquery_results.size();
        if (left_row_count > 1) {
          return RC::SUBQUERY_TOO_MANY_ROWS;
        }
        left_value = left_subquery_results[0];

        result = true;
        for (int i = 0; i < right_subquery_results.size(); i++) {
          right_value     = right_subquery_results[i];
          bool bool_value = false;
          rc              = compare_value(left_value, right_value, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = false;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      } break;
      case CompOp::EQUAL_TO:
      case CompOp::GREAT_EQUAL:
      case CompOp::GREAT_THAN:
      case CompOp::LESS_EQUAL:
      case CompOp::LESS_THAN:
      case CompOp::NOT_EQUAL: {
        // check the row number
        int left_row_count = left_subquery_results.size();
        if (left_row_count > 1) {
          return RC::SUBQUERY_TOO_MANY_ROWS;
        }
        left_value = left_subquery_results[0];

        int right_row_count = right_subquery_results.size();
        if (right_row_count > 1) {
          return RC::SUBQUERY_TOO_MANY_ROWS;
        }

        // set default result
        result = false;

        if (left_row_count == 1 && right_row_count == 1) {
          left_value  = left_subquery_results[0];
          right_value = right_subquery_results[0];
          rc          = compare_value(left_value, right_value, result);
          if (rc != RC::SUCCESS)
            return rc;
        }

        return RC::SUCCESS;
      } break;
    }
  } else if (left_->type() == ExprType::SUB_QUERY & right_->type() != ExprType::SUB_QUERY) {
    // open sub-query operator, execute sub-query if has not executed
    OperExpr *oper = dynamic_cast<OperExpr *>(left_.get());
    rc             = oper->catch_subquery_results();
    if (rc != RC::SUCCESS)
      return rc;

    std::vector<Value> &subquery_results = oper->get_subquery_results();
    switch (comp_) {
      case CompOp::IN_OP: {
        result = false;
        for (int i = 0; i < subquery_results.size(); i++) {
          left_value      = subquery_results[i];
          bool bool_value = false;
          rc              = compare_value(left_value, right, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = true;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      } break;
      case CompOp::NOT_IN_OP: {
        result = true;

        for (int i = 0; i < subquery_results.size(); i++) {
          left_value      = subquery_results[i];
          bool bool_value = false;
          rc              = compare_value(left_value, right, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = false;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      } break;
      case CompOp::EQUAL_TO:
      case CompOp::GREAT_EQUAL:
      case CompOp::GREAT_THAN:
      case CompOp::LESS_EQUAL:
      case CompOp::LESS_THAN:
      case CompOp::NOT_EQUAL: {
        // check the row number
        int row_count = subquery_results.size();
        if (row_count > 1) {
          return RC::SUBQUERY_TOO_MANY_ROWS;
        }

        // set default result
        result = false;

        if (row_count == 1) {
          left_value = subquery_results[0];
          rc         = compare_value(left_value, right, result);
          if (rc != RC::SUCCESS)
            return rc;
        }

        return RC::SUCCESS;
      } break;
    }
  } else if (left_->type() != ExprType::SUB_QUERY & right_->type() == ExprType::SUB_QUERY) {
    // open sub-query operator, execute sub-query if has not executed
    OperExpr *oper = dynamic_cast<OperExpr *>(right_.get());
    rc             = oper->catch_subquery_results();
    if (rc != RC::SUCCESS)
      return rc;

    std::vector<Value> &subquery_results = oper->get_subquery_results();
    switch (comp_) {
      case CompOp::IN_OP: {
        result = false;
        for (int i = 0; i < subquery_results.size(); i++) {
          right_value     = subquery_results[i];
          bool bool_value = false;
          rc              = compare_value(left, right_value, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = true;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      }
      case CompOp::NOT_IN_OP: {
        result = true;

        for (int i = 0; i < subquery_results.size(); i++) {
          right_value     = subquery_results[i];
          bool bool_value = false;
          rc              = compare_value(left, right_value, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = false;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      }
      case CompOp::EQUAL_TO:
      case CompOp::GREAT_EQUAL:
      case CompOp::GREAT_THAN:
      case CompOp::LESS_EQUAL:
      case CompOp::LESS_THAN:
      case CompOp::NOT_EQUAL: {
        // check the row number
        int row_count = subquery_results.size();
        if (row_count > 1) {
          return RC::SUBQUERY_TOO_MANY_ROWS;
        }

        // set default result
        result = false;

        if (row_count == 1) {
          right_value = subquery_results[0];
          rc          = compare_value(left, right_value, result);
          if (rc != RC::SUCCESS)
            return rc;
        }

        return RC::SUCCESS;
      } break;
    }
  } else {
    return RC::NO_SUBQUERY;
  }
  return RC::SUCCESS;
}

RC ComparisonExpr::compare_valuelist(const Value &left, const Value &right, bool &result) const
{
  RC       rc;
  RowTuple tuple;
  Value    left_value;
  Value    right_value;

  if (left_->type() == ExprType::VALUELIST & right_->type() != ExprType::VALUELIST) {
    // open sub-query operator, execute sub-query if has not executed
    ValueListExpr *vlexpr = dynamic_cast<ValueListExpr *>(left_.get());
    vector<Value>  vl     = vlexpr->get_valuelist();
    switch (comp_) {
      case CompOp::IN_OP: {
        result = false;
        for (int i = 0; i < vl.size(); i++) {
          left_value      = vl[i];
          bool bool_value = false;
          rc              = compare_value(left_value, right, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = true;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
            return rc;
          }
        }

        return RC::SUCCESS;
      } break;
      case CompOp::NOT_IN_OP: {
        result = true;

        for (int i = 0; i < vl.size(); i++) {
          left_value      = vl[i];
          bool bool_value = false;
          rc              = compare_value(left_value, right, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = false;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      } break;
      case CompOp::EQUAL_TO:
      case CompOp::GREAT_EQUAL:
      case CompOp::GREAT_THAN:
      case CompOp::LESS_EQUAL:
      case CompOp::LESS_THAN:
      case CompOp::NOT_EQUAL: {
        // check the row number
        int row_count = vl.size();
        if (row_count > 1) {
          return RC::SUBQUERY_TOO_MANY_ROWS;
        }

        // set default result
        result = false;

        if (row_count == 1) {
          left_value = vl[0];
          rc         = compare_value(left_value, right, result);
          if (rc != RC::SUCCESS)
            return rc;
        }

        return RC::SUCCESS;
      } break;
    }
  } else if (left_->type() != ExprType::VALUELIST & right_->type() == ExprType::VALUELIST) {
    // open sub-query operator, execute sub-query if has not executed
    ValueListExpr *vlexpr = dynamic_cast<ValueListExpr *>(right_.get());
    vector<Value>  vl     = vlexpr->get_valuelist();
    switch (comp_) {
      case CompOp::IN_OP: {
        result = false;
        for (int i = 0; i < vl.size(); i++) {
          right_value     = vl[i];
          bool bool_value = false;
          rc              = compare_value(left, right_value, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = true;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      }
      case CompOp::NOT_IN_OP: {
        result = true;

        for (int i = 0; i < vl.size(); i++) {
          right_value     = vl[i];
          bool bool_value = false;
          rc              = compare_value(left, right_value, bool_value);
          if (rc == RC::SUCCESS) {
            if (bool_value) {
              result = false;
              return rc;
            }
          } else {
            LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
            return rc;
          }
        }
        return RC::SUCCESS;
      }
      case CompOp::EQUAL_TO:
      case CompOp::GREAT_EQUAL:
      case CompOp::GREAT_THAN:
      case CompOp::LESS_EQUAL:
      case CompOp::LESS_THAN:
      case CompOp::NOT_EQUAL: {
        // check the row number
        int row_count = vl.size();
        if (row_count > 1) {
          return RC::SUBQUERY_TOO_MANY_ROWS;
        }

        // set default result
        result = false;

        if (row_count == 1) {
          right_value = vl[0];
          rc          = compare_value(left, right_value, result);
          if (rc != RC::SUCCESS)
            return rc;
        }

        return RC::SUCCESS;
      } break;
    }
  }

  return RC::SUCCESS;
}

RC ComparisonExpr::like_operation(const Value &left, const Value &right, bool &result, bool do_like) const
{
  auto rc = RC::SUCCESS;
  if (left.attr_type() != right.attr_type() || left.attr_type() != AttrType::CHARS) {
    LOG_WARN("Only char field can use the like operation");
    return RC::INTERNAL;
  }
  std::regex     reg;
  constexpr auto alias_of_single_char_wildcard = "[^']{1}";
  constexpr auto alias_of_chars_wildcard       = "[^']*";
  std::string    pattern{};

  for (char i : right.get_string()) {
    if (i == '_') {
      pattern += alias_of_single_char_wildcard;
    } else if (i == '%') {
      pattern += alias_of_chars_wildcard;
    } else {
      pattern += i;
    }
  }
  std::regex re(pattern);
  auto       str = left.get_string();

  if (std::regex_match(str.begin(), str.end(), re)) {
    result = do_like == true;
  } else {
    result = do_like == false;
  }
  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr   *left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr   *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value)
{
  RC    rc;
  Value left_value;
  Value right_value;

  left_->set_parent_query_tuples(get_parent_query_tuples());
  right_->set_parent_query_tuples(get_parent_query_tuples());

  if (left_->type() == ExprType::VALUE || left_->type() == ExprType::FIELD || left_->type() == ExprType::ARITHMETIC) {
    rc = left_->get_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  if (right_->type() == ExprType::VALUE || right_->type() == ExprType::FIELD ||
      right_->type() == ExprType::ARITHMETIC) {
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  bool bool_value = false;
  if (left_->type() == ExprType::SUB_QUERY | right_->type() == ExprType::SUB_QUERY) {  // there is a subquery
    rc = compare_sub_query(left_value, right_value, bool_value);
    if (rc == RC::SUCCESS) {
      value.set_boolean(bool_value);
    } else {
      return rc;
    }
  } else if (left_->type() == ExprType::VALUELIST | right_->type() == ExprType::VALUELIST) {  // there is a value list
    rc = compare_valuelist(left_value, right_value, bool_value);
    if (rc == RC::SUCCESS) {
      value.set_boolean(bool_value);
    } else {
      return rc;
    }
  } else {  // normal comparison
    rc = compare_value(left_value, right_value, bool_value);
    if (rc == RC::SUCCESS) {
      value.set_boolean(bool_value);
    } else {
      return rc;
    }
  }

  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    expr->set_parent_query_tuples(get_parent_query_tuples());
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  if (left_value.get_isnull() || right_value.get_isnull()) {
    value.set_isnull();
    return rc;
  }
  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE:
          // 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          // value.set_int(numeric_limits<int>::max());
          value.set_isnull();
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE:
          // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          // value.set_float(numeric_limits<float>::max());
          value.set_isnull();
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if (right_) {
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

// try to get value from sub-query
RC OperExpr::get_value(const Tuple &tuple, Value &value)
{
  physic_oper_->set_parent_query_tuples(get_parent_query_tuples());
  RC rc = physic_oper_->next();
  if (rc == RC::SUCCESS) {
    Tuple *sub_query_tuple = physic_oper_->current_tuple();
    int    cell_num        = sub_query_tuple->cell_num();
    if (cell_num > 1) {
      return RC::SUBQUERY_TOO_MANY_COLUMNS;
    }
    rc = sub_query_tuple->cell_at(0, value);
    return rc;
  } else {
    return rc;
  }
}

RC OperExpr::catch_subquery_results()
{
  RC       rc;
  RowTuple tuple;

  // reopen operator
  rc = physic_oper_->open();
  if (rc != RC::SUCCESS)
    return rc;

  // start to load data
  subquery_results.clear();
  while (true) {
    Value value;
    rc = get_value(tuple, value);
    if (rc == RC::SUCCESS)
      subquery_results.push_back(value);
    else if (rc == RC::RECORD_EOF)
      break;
    else
      return rc;
  }

  return RC::SUCCESS;
}