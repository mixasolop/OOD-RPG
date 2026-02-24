#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "Item.h"

using namespace std;


class World;

class Player {
public:
    struct Attributes {
        int strength;
        int dexterity;
        int health;
        int luck;
        int aggression;
        int wisdom;
    };

private:
    int row;
    int col;
    Attributes stats;
    vector<unique_ptr<Item>> inventory;
    unique_ptr<Item> leftHand;
    unique_ptr<Item> rightHand;
    int gold;
    int coins;

public:
    Player();

    int getRow() const{return row;};
    int getCol() const{return col;};
    void setPosition(int row, int col);

    const Attributes& getAttributes() const;

    vector<unique_ptr<Item>>& getInventory();

    const Item* getLeftHand() const {return leftHand.get();};
    const Item* getRightHand() const {return rightHand.get();};

    int getGold() const {return gold;};
    int getCoins() const {return coins;};

    bool move(int dRow, int dCol, const World& world);
    void pickUp(unique_ptr<Item> item);
    unique_ptr<Item> dropItem(size_t index);

    bool equipItem(size_t index, bool equipLeftHand);
    bool unequipItem(bool fromLeftHand);
};


