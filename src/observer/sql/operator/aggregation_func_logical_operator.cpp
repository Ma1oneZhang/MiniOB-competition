#include "aggregation_func_logical_operator.h"

AggregationLogicalOperator::AggregationLogicalOperator(
    Table *tables, const std::vector<Field> &fields, const std::vector<Field> &group_by)
    : tables_(tables), fields_(fields), group_by_fields_(group_by)
{}