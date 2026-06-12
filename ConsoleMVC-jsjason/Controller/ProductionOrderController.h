#pragma once
#include "../Model/ProductionOrder.h"
#include "../View/ProductionOrderView.h"

class ProductionOrderController {
public:
    ProductionOrderController(ProductionOrderRepository& repo,
                              ProductionOrderView&       view);

    void Run();

private:
    void HandleList();
    void HandleCreate();
    void HandleUpdateStatus();
    void HandleDelete();

    ProductionOrderRepository& _repo;
    ProductionOrderView&       _view;
};
