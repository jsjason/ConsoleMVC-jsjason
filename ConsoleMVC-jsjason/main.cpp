#include "Model/ProductionOrder.h"
#include "View/ProductionOrderView.h"
#include "Controller/ProductionOrderController.h"
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    ProductionOrderRepository repo;
    ProductionOrderView       view;
    ProductionOrderController controller(repo, view);

    controller.Run();
    return 0;
}
