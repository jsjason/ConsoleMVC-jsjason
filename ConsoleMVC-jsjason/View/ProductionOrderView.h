#pragma once
#include <vector>
#include "../Model/ProductionOrder.h"

class ProductionOrderView {
public:
    void ShowMenu() const;
    void ShowOrderList(const std::vector<ProductionOrder>& orders) const;
    void ShowOrder(const ProductionOrder& order) const;
    void ShowMessage(const std::string& message) const;
    void ShowError(const std::string& message) const;

    int         PromptInt(const std::string& prompt) const;
    std::string PromptString(const std::string& prompt) const;
};
