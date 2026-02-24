#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "Item.h"

using namespace std;


class Tile {
private:
    bool wall;
    vector<unique_ptr<Item>> items;

public:
    Tile(){};
    explicit Tile(bool wall) {this->wall = wall;};

    bool isWall() const {return wall;};
    void setWall(bool value);

    bool hasItems() const {return !items.empty();};
    const vector<unique_ptr<Item>>& getItems() const { return items; };
    vector<unique_ptr<Item>>& getItems() {return items;};
    void addItem(unique_ptr<Item> item);
    unique_ptr<Item> takeItem(size_t index);
};


