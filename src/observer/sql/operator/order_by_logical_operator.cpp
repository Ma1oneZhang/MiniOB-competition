#include "sql/operator/order_by_logical_operator.h"
OrderByLogicalOperator::OrderByLogicalOperator(std::vector<OrderBySqlNode> *fields) : fields_(fields) {}