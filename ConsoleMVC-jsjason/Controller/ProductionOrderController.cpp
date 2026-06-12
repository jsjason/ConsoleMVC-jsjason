#include "ProductionOrderController.h"
#include <iostream>

ProductionOrderController::ProductionOrderController(
    ProductionOrderRepository& repo, ProductionOrderView& view)
    : _repo(repo), _view(view) {}

void ProductionOrderController::Run() {
    while (true) {
        _view.ShowMenu();
        int choice = _view.PromptInt("");
        switch (choice) {
            case 1: HandleList();         break;
            case 2: HandleCreate();       break;
            case 3: HandleUpdateStatus(); break;
            case 4: HandleDelete();       break;
            case 0:
                _view.ShowMessage("시스템을 종료합니다.");
                return;
            default:
                _view.ShowError("잘못된 선택입니다.");
        }
    }
}

void ProductionOrderController::HandleList() {
    _view.ShowOrderList(_repo.GetAll());
}

void ProductionOrderController::HandleCreate() {
    std::string name = _view.PromptString("제품명: ");
    int qty          = _view.PromptInt("수량: ");

    if (name.empty() || qty <= 0) {
        _view.ShowError("유효하지 않은 입력입니다.");
        return;
    }

    ProductionOrder order{0, name, qty, OrderStatus::Pending};
    _repo.Add(order);
    _view.ShowMessage("주문이 등록되었습니다.");
}

void ProductionOrderController::HandleUpdateStatus() {
    _view.ShowOrderList(_repo.GetAll());
    int id = _view.PromptInt("변경할 주문 ID: ");

    if (!_repo.FindById(id)) {
        _view.ShowError("해당 ID의 주문이 없습니다.");
        return;
    }

    std::cout << "  1.대기중  2.진행중  3.완료  4.취소\n";
    int s = _view.PromptInt("상태 선택: ");

    OrderStatus status;
    switch (s) {
        case 1: status = OrderStatus::Pending;    break;
        case 2: status = OrderStatus::InProgress; break;
        case 3: status = OrderStatus::Completed;  break;
        case 4: status = OrderStatus::Cancelled;  break;
        default:
            _view.ShowError("잘못된 상태 값입니다.");
            return;
    }

    _repo.UpdateStatus(id, status);
    _view.ShowMessage("상태가 변경되었습니다.");
}

void ProductionOrderController::HandleDelete() {
    _view.ShowOrderList(_repo.GetAll());
    int id = _view.PromptInt("삭제할 주문 ID: ");

    if (_repo.Remove(id))
        _view.ShowMessage("주문이 삭제되었습니다.");
    else
        _view.ShowError("해당 ID의 주문이 없습니다.");
}
