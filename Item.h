#pragma once

#include <string>

using namespace std;


class Item {
protected:
    string name;
    char symbol;

public:
    Item(const string& name, char symbol) {this->name = name; this->symbol = symbol;};
    virtual ~Item();

    const string& getName() const {return name;};
    char getSymbol() const {return symbol;};

    virtual string getDescription() const;
    virtual bool canEquip() const;
    virtual bool isTwoHanded() const;
    virtual int getDamage() const;
    virtual bool isCurrency() const;
    virtual void collectCurrency(int& coins, int& gold) const;
};


