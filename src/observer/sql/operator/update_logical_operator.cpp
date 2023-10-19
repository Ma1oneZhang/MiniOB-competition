#include "update_logical_operator.h"
#include "sql/parser/value.h"
#include <string>
#include <vector>

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, std::vector<std::string> *attribute_names, Value *values, int value_amount)
    : table_(table), attribute_names_(attribute_names), values_(values), value_amount_(value_amount)
{
}