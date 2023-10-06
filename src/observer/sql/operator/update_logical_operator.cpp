#include "update_logical_operator.h"
#include "sql/parser/value.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const char *attribute_name, Value *values, int value_amount)
    : table_(table), attribute_name_(attribute_name), values_(values), value_amount_(value_amount)
{
}