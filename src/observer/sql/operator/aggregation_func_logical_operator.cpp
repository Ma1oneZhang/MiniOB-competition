#include "aggregation_func_logical_operator.h"

AggregationLogicalOperator::AggregationLogicalOperator(
    const std::vector<Field> &fields, const std::vector<Field> &group_by)
    : fields_(fields), group_by_fields_(group_by)
{}