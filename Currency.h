#pragma once

#include <string>

#include "Item.h"

class Currency : public Item {
private:
    int amount;
    bool goldType;

public:
    Currency(const std::string& name, char symbol, int amount, bool goldType);

    bool isCurrency() const override;
    void collectCurrency(int& coins, int& gold) const override;
    std::string getDescription() const override;
};
