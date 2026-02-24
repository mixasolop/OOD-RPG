#pragma once

#include <string>

#include "Item.h"

using namespace std;


class MiscItem : public Item {
public:
    MiscItem(const string& name, char symbol);

    string getDescription() const override;
};


