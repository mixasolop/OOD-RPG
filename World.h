#pragma once

#include <vector>

#include "Tile.h"

using namespace std;


class World {
public:
    static constexpr int Rows = 20;
    static constexpr int Cols = 40;

private:
    vector<vector<Tile>> grid;

public:
    World();

    bool isInside(int row, int col) const;
    bool isWalkable(int row, int col) const;

    Tile& at(int row, int col) {return grid[row][col];};
    const Tile& at(int row, int col) const {return grid[row][col];};

    int getRows() {return Rows;};
    int getCols() {return Cols;};

    const int& getRows() const {return Rows;};
    const int& getCols() const {return Cols;};

};


