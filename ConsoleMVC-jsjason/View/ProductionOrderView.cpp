#include "ProductionOrderView.h"
#include <iostream>
#include <iomanip>

void ProductionOrderView::ShowMenu() const {
    std::cout << "\n========== 생산주문 관리 시스템 ==========\n"
              << "  1. 주문 목록 조회\n"
              << "  2. 주문 등록\n"
              << "  3. 주문 상태 변경\n"
              << "  4. 주문 삭제\n"
              << "  0. 종료\n"
              << "==========================================\n"
              << "선택: ";
}

void ProductionOrderView::ShowOrderList(const std::vector<ProductionOrder>& orders) const {
    if (orders.empty()) {
        std::cout << "  (등록된 주문이 없습니다)\n";
        return;
    }
    std::cout << "\n"
              << std::left
              << std::setw(6)  << "ID"
              << std::setw(20) << "제품명"
              << std::setw(8)  << "수량"
              << std::setw(10) << "상태"
              << "\n"
              << std::string(44, '-') << "\n";

    for (const auto& o : orders) {
        std::cout << std::setw(6)  << o.id
                  << std::setw(20) << o.productName
                  << std::setw(8)  << o.quantity
                  << std::setw(10) << OrderStatusToString(o.status)
                  << "\n";
    }
}

void ProductionOrderView::ShowOrder(const ProductionOrder& order) const {
    std::cout << "\n[주문 상세]\n"
              << "  ID     : " << order.id << "\n"
              << "  제품명 : " << order.productName << "\n"
              << "  수량   : " << order.quantity << "\n"
              << "  상태   : " << OrderStatusToString(order.status) << "\n";
}

void ProductionOrderView::ShowMessage(const std::string& message) const {
    std::cout << "  >> " << message << "\n";
}

void ProductionOrderView::ShowError(const std::string& message) const {
    std::cerr << "  [오류] " << message << "\n";
}

int ProductionOrderView::PromptInt(const std::string& prompt) const {
    int value;
    std::cout << prompt;
    std::cin >> value;
    std::cin.ignore();
    return value;
}

std::string ProductionOrderView::PromptString(const std::string& prompt) const {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}
