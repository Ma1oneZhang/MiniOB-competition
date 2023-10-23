#include "common/log/log.h"
#include <future>
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "storage/trx/trx.h"
// #include <boost/sort/parallel_stable_sort/parallel_stable_sort.hpp>
#include "sql/operator/order_by_physical_operator.h"
#include <chrono>
#include <vector>

class cmp
{
public:
  cmp(std::vector<OrderBySqlNode> *o) : order_by_nodes_(o){};
  bool operator()(Tuple *lhs, Tuple *rhs)
  {
    for (auto &order_node : *order_by_nodes_) {
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
  std::vector<OrderBySqlNode> *order_by_nodes_;
};

void parallel_merge_sort(vector<Tuple *>::iterator begin, vector<Tuple *>::iterator end, cmp &cmp)
{
  auto mid = begin + (end - begin) / 2;
  if (end - begin > 128) {
    auto f1 = std::async(std::launch::async, [&]() { parallel_merge_sort(begin, mid, cmp); });
    auto f2 = std::async(std::launch::async, [&]() { parallel_merge_sort(mid, end, cmp); });
    f1.wait();
    f2.wait();
  } else {
    std::inplace_merge(begin, mid, end, cmp);
  }
}

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

RC SortPhysicalOperator::next()
{
  if (pos == -1) {
    RC rc = RC::SUCCESS;
    while (RC::SUCCESS == (rc = child_->next())) {
      tuples.push_back(child_->current_tuple());
    }
    cmp cmp(order_by_nodes_);
    parallel_merge_sort(tuples.begin(), tuples.end(), cmp);
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