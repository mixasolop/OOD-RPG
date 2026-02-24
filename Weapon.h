#pragma once

#include <string>

#include "Item.h"

using namespace std;


class Weapon : public Item {
private:
    int damage;
    bool twoHanded;

public:
    Weapon(const string& name, char symbol, int damage, bool twoHanded) :
        Item(name, symbol), damage(damage), twoHanded(twoHanded) {};

    bool canEquip() const override { return true; };
    bool isTwoHanded() const override { return twoHanded; };
    int getDamage() const override { return damage; };
    string getDescription() const override {
        string txt = name + " (weapon, dmg " + to_string(damage) + ")";
        if (twoHanded) txt += " [2H]";
        else txt += " [1H]";
        return txt;
    }
};


