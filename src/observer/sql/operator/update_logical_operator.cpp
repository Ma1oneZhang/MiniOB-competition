#include "update_logical_operator.h"
#include <string>
#include <vector>

UpdateLogicalOperator::UpdateLogicalOperator(
    Table *table, std::vector<std::string> &&attribute_names, std::vector<LazyValue> &&lazy_values)
    : table_(table), attribute_names_(attribute_names)
{
  values_.swap(lazy_values);
}