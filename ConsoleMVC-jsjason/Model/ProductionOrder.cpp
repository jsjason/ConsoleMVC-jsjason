#include "ProductionOrder.h"
#include <algorithm>

std::string OrderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Pending:    return "대기중";
        case OrderStatus::InProgress: return "진행중";
        case OrderStatus::Completed:  return "완료";
        case OrderStatus::Cancelled:  return "취소";
        default:                      return "알수없음";
    }
}

void ProductionOrderRepository::Add(const ProductionOrder& order) {
    ProductionOrder newOrder = order;
    newOrder.id = _nextId++;
    _orders.push_back(newOrder);
}

bool ProductionOrderRepository::UpdateStatus(int id, OrderStatus status) {
    for (auto& o : _orders) {
        if (o.id == id) {
            o.status = status;
            return true;
        }
    }
    return false;
}

bool ProductionOrderRepository::Remove(int id) {
    auto it = std::remove_if(_orders.begin(), _orders.end(),
        [id](const ProductionOrder& o) { return o.id == id; });
    if (it == _orders.end()) return false;
    _orders.erase(it, _orders.end());
    return true;
}

const ProductionOrder* ProductionOrderRepository::FindById(int id) const {
    for (const auto& o : _orders) {
        if (o.id == id) return &o;
    }
    return nullptr;
}

const std::vector<ProductionOrder>& ProductionOrderRepository::GetAll() const {
    return _orders;
}
