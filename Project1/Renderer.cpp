#include "Renderer.h"

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>

#include "Item.h"
#include "Player.h"
#include "World.h"

using namespace std;

namespace {
    string itemToText(const Item* item) {
        if (item == nullptr) {
            return "(empty)";
        }
        return item->getName();
    }

    string tileItemToText(const Item* item) {
        if (item == nullptr) {
            return "?";
        }

        string text;
        text.push_back(item->getSymbol());
        text += " ";
        text += item->getName();
        return text;
    }
}

namespace {
    void moveCursorTopLeft() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos{ 0, 0 };
        SetConsoleCursorPosition(h, pos);
    }

    void moveCursorTo(int row, int col) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos{ static_cast<SHORT>(col), static_cast<SHORT>(row) };
        SetConsoleCursorPosition(h, pos);
    }

    void writeAt(int row, int col, const string& text) {
        moveCursorTo(row, col);
        cout << text;
    }

    void hideCursor() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO ci{};
        ci.dwSize = 1;
        ci.bVisible = FALSE;
        SetConsoleCursorInfo(h, &ci);
    }
    void clearRenderArea(int width, int height) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD topLeft{ 0, 0 };

        SetConsoleCursorPosition(h, topLeft);

        for (int r = 0; r < height; ++r) {
            cout << string(width, ' ') << '\n';
        }

        SetConsoleCursorPosition(h, topLeft);
    }
}

Renderer::Renderer() {
    hideCursor();
}

void Renderer::draw(const World& world, const Player& player) const {
    const int rows = world.getRows();
    const int cols = world.getCols();

    vector<string> side;

    const Player::Attributes& a = player.getAttributes();
    side.push_back("PLAYER");
    side.push_back("STR: " + to_string(a.strength));
    side.push_back("DEX: " + to_string(a.dexterity));
    side.push_back("HP : " + to_string(a.health));
    side.push_back("LUK: " + to_string(a.luck));
    side.push_back("AGR: " + to_string(a.aggression));
    side.push_back("WIS: " + to_string(a.wisdom));
    side.push_back("");

    side.push_back("EQUIPPED");
    side.push_back("L: " + itemToText(player.getLeftHand()));
    side.push_back("R: " + itemToText(player.getRightHand()));
    side.push_back("");

    side.push_back("WALLET");
    side.push_back("Coins: " + to_string(player.getCoins()));
    side.push_back("Gold : " + to_string(player.getGold()));
    side.push_back("");

    side.push_back("INVENTORY");
    vector<unique_ptr<Item>>& inv = const_cast<Player&>(player).getInventory();
    if (inv.empty()) {
        side.push_back("(empty)");
    }
    else {
        for (size_t i = 0; i < inv.size(); ++i) {
            string line = to_string(i) + ": " + inv[i]->getDescription();
            if ((int)i == player.getInvIdx()) line += " <";
            side.push_back(line);
        }
    }
    side.push_back("");

    side.push_back("ON THIS TILE");
    const Tile& current = world.at(player.getRow(), player.getCol());
    if (!current.hasItems()) {
        side.push_back("(none)");
    }
    else {
        const vector<unique_ptr<Item>>& items = current.getItems();
        for (size_t i = 0; i < items.size(); ++i) {
            side.push_back(tileItemToText(items[i].get()));
        }
    }

    vector<string> map(rows, string(cols, ' '));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char ch = ' ';
            if (player.getRow() == r && player.getCol() == c) ch = '¶';
            else {
                const Tile& tile = world.at(r, c);
                if (tile.isWall()) ch = '█';
                else if (tile.hasItems()) {
                    const vector<unique_ptr<Item>>& items = tile.getItems();
                    if (!items.empty() && items[0] != nullptr) ch = items[0]->getSymbol();
                }
            }
            map[r][c] = ch;
        }
    }

    static bool initialized = false;
    static vector<string> prevMap;
    static vector<string> prevSide;
    static int prevRows = 0;
    static int prevCols = 0;
    static int prevRenderWidth = 0;
    static int prevRenderHeight = 0;

    int maxSide = 0;
    for (const auto& s : side) maxSide = max(maxSide, (int)s.size());
    const int renderHeight = max(rows, (int)side.size());
    const int renderWidth = cols + 3 + maxSide;

    const bool shapeChanged = (!initialized || rows != prevRows || cols != prevCols);
    if (shapeChanged) {
        const int clearHeight = max(renderHeight, prevRenderHeight);
        const int clearWidth = max(renderWidth, prevRenderWidth);
        clearRenderArea(clearWidth, clearHeight);
        initialized = false;
    }

    if (!initialized) {
        for (int r = 0; r < rows; ++r) {
            writeAt(r, 0, map[r]);
            if (r < (int)side.size()) {
                writeAt(r, cols + 3, side[r]);
            }
        }

        for (int r = rows; r < (int)side.size(); ++r) {
            writeAt(r, cols + 3, side[r]);
        }
        initialized = true;
    }
    else {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (map[r][c] != prevMap[r][c]) {
                    string ch(1, map[r][c]);
                    writeAt(r, c, ch);
                }
            }
        }

        const int maxLines = max((int)prevSide.size(), (int)side.size());
        for (int r = 0; r < maxLines; ++r) {
            const string oldLine = (r < (int)prevSide.size()) ? prevSide[r] : "";
            const string newLine = (r < (int)side.size()) ? side[r] : "";
            if (oldLine != newLine) {
                string out = newLine;
                if (oldLine.size() > newLine.size()) {
                    out += string(oldLine.size() - newLine.size(), ' ');
                }
                writeAt(r, cols + 3, out);
            }
        }
    }

    moveCursorTopLeft();
    cout.flush();

    prevMap = move(map);
    prevSide = move(side);
    prevRows = rows;
    prevCols = cols;
    prevRenderWidth = renderWidth;
    prevRenderHeight = renderHeight;
}

