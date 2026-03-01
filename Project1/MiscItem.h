#pragma once

#include <string>

#include "Item.h"

using namespace std;


class MiscItem : public Item {
public:
    MiscItem(const string& name, char symbol) :Item(name, symbol) {};

    string getDescription() const override {
        string txt = name + " (unusable)";
        return txt;
    };
};


