#pragma once
#include <string>
#include <vector>

enum class OrderStatus {
    Pending,
    InProgress,
    Completed,
    Cancelled
};

std::string OrderStatusToString(OrderStatus status);

struct ProductionOrder {
    int         id;
    std::string productName;
    int         quantity;
    OrderStatus status;
};

class ProductionOrderRepository {
public:
    void                              Add(const ProductionOrder& order);
    bool                              UpdateStatus(int id, OrderStatus status);
    bool                              Remove(int id);
    const ProductionOrder*            FindById(int id) const;
    const std::vector<ProductionOrder>& GetAll() const;

private:
    std::vector<ProductionOrder> _orders;
    int                          _nextId = 1;
};
