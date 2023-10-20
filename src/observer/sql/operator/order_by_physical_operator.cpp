#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "storage/trx/trx.h"
#include "sql/operator/order_by_physical_operator.h"

RC SortPhysicalOperator::open(Trx *trx)
{
  assert(children_.size() == 1);
  auto rc = children_.front()->open(trx);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  child_     = children_.front().get();
  this->trx_ = trx;

  return RC::SUCCESS;
}

bool SortPhysicalOperator::cmp(JoinedTuple *lhs, JoinedTuple *rhs)
{
  for (auto &order_node : *this->order_by_nodes_) {
    Value lv, rv;
    lhs->find_cell({order_node.relation_name.c_str(), order_node.attribute_name.c_str()}, lv);
    rhs->find_cell({order_node.relation_name.c_str(), order_node.attribute_name.c_str()}, rv);
    int result = lv.compare(rv);
    if (result == 0) {
      continue;
    } else if (result > 0) {
      // lhs is bigger
      return order_node.is_desc == true;
    } else {
      // rhs is bigger
      return order_node.is_desc != true;
    }
  }
  return false;
}

RC SortPhysicalOperator::next()
{
  if (pos == -1) {
    RC rc = RC::SUCCESS;
    while (RC::SUCCESS == (rc = child_->next())) {
      tuples.push_back(static_cast<JoinedTuple *>(child_->current_tuple()));
    }
    std::sort(tuples.begin(), tuples.end(), [this](JoinedTuple *lhs, JoinedTuple *rhs) { return this->cmp(lhs, rhs); });
    LOG_WARN("We sorted %d tuple", tuples.size());
  }
  pos++;
  if (pos == tuples.size()) {
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}

Tuple *SortPhysicalOperator::current_tuple() { return tuples[pos]; }

RC SortPhysicalOperator::close()
{
  auto rc = child_->close();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  this->tuples.clear();
  return rc;
}