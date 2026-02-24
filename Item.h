#pragma once

#include <string>

using namespace std;


class Item {
protected:
    string name;
    char symbol;
public:
    Item(const string& name, char symbol) {this->name = name; this->symbol = symbol;};
    virtual ~Item() {};

    const string& getName() const {return name;};
    char getSymbol() const {return symbol;};

    virtual string getDescription() const { return name; }
    virtual bool canEquip() const { return false; }
    virtual bool isTwoHanded() const { return false; }
    virtual int getDamage() const { return 0; }
    virtual bool isCurrency() const { return false; }
    virtual void collectCurrency(int& coins, int& gold) const { }
};

