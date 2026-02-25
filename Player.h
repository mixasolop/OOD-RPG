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
    unique_ptr<Item> leftHand = nullptr;
    unique_ptr<Item> rightHand = nullptr;
    int gold;
    int coins;
    int inventoryIdx = 0;

public:
    Player();

    int getRow() const{return row;};
    int getCol() const{return col;};
    void setPosition(int row, int col) { this->row = row; this->col = col; };

    const Attributes& getAttributes() const;

    vector<unique_ptr<Item>>& getInventory();

    const Item* getLeftHand() const {return leftHand.get();};
    const Item* getRightHand() const {return rightHand.get();};

    int getGold() const {return gold;};
    int getCoins() const {return coins;};

    void pickUp(unique_ptr<Item> item) { inventory.push_back(move(item)); };
    unique_ptr<Item> dropItem(size_t index);

    void moveInventory(bool Up);
    const int getInvIdx() const { return inventoryIdx; };

    bool equipItem(bool equipLeftHand);
    bool unequipItem(bool fromLeftHand);
};


