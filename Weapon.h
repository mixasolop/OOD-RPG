#pragma once

#include <string>

#include "Item.h"

using namespace std;


class Weapon : public Item {
private:
    int damage;
    bool twoHanded;

public:
    Weapon(const string& name, char symbol, int damage, bool twoHanded);

    bool canEquip() const override;
    bool isTwoHanded() const override;
    int getDamage() const override;
    string getDescription() const override;
};


