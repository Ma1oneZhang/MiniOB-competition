#include "aggregation_func_logical_operator.h"

AggregationLogicalOperator::AggregationLogicalOperator(Table * tables, const std::vector<Field> &fields)
    : tables_(tables), fields_(fields)
{}