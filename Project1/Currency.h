#pragma once

#include <string>

#include "Item.h"

class Currency : public Item {
private:
    int amount;
    bool goldType;

public:
    Currency(const std::string& name, char symbol, int amount, bool goldType) : Item(name, symbol), amount(amount), goldType(goldType) {};

    bool isCurrency() const override { return true; };
    void collectCurrency(int& coins, int& gold) const override {
        if (goldType) gold += amount;
        else coins += amount;
    };
    std::string getDescription() const override {
        return name + " +" + std::to_string(amount);
    };
};