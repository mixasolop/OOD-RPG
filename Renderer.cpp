#include "Renderer.h"

#include <iostream>
#include <string>
#include <vector>

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
}  // namespace

Renderer::Renderer() {
}

void Renderer::draw(const World& world, const Player& player) const {
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
    } else {
        for (size_t i = 0; i < inv.size(); ++i) {
            string line = to_string(i);
            line += ": ";
            line += inv[i].get()->getDescription();
            if (i == player.getInvIdx()) {
                line += " <";
            }
            side.push_back(line);
        }
    }
    side.push_back("");

    side.push_back("ON THIS TILE");
    const Tile& current = world.at(player.getRow(), player.getCol());
    if (!current.hasItems()) {
        side.push_back("(none)");
    } else {
        const vector<unique_ptr<Item>>& items = current.getItems();
        for (size_t i = 0; i < items.size(); ++i) {
            side.push_back(tileItemToText(items[i].get()));
        }
    }

    const int rows = world.getRows();
    const int cols = world.getCols();

    for (int r = 0; r < rows; ++r) {
        string rowText;
        rowText.reserve(cols);

        for (int c = 0; c < cols; ++c) {
            char ch = ' ';

            if (player.getRow() == r && player.getCol() == c) {
                ch = '¶';
            } else {
                const Tile& tile = world.at(r, c);
                if (tile.isWall()) {
                    ch = '█';
                } else if (tile.hasItems()) {
                    const vector<unique_ptr<Item>>& items = tile.getItems();
                    if (!items.empty() && items[0] != nullptr) {
                        ch = items[0]->getSymbol();
                    }
                }
            }

            rowText.push_back(ch);
        }

        cout << rowText;
        if (r < static_cast<int>(side.size())) {
            cout << "   " << side[r];
        }
        cout << '\n';
    }

    for (int r = rows; r < static_cast<int>(side.size()); ++r) {
        cout << string(cols, ' ') << "   " << side[r] << '\n';
    }
}
