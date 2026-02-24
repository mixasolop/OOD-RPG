#include "Tile.h"

using namespace std;


// No function definitions yet.

void Tile::addItem(unique_ptr<Item> item)
{
    if (item != nullptr) {
        items.push_back(move(item));
    }
}

unique_ptr<Item> Tile::takeItem(size_t index)
{
    unique_ptr<Item> tmp = move(items[index]);
    items.erase(items.begin()+index);
    return tmp;
}
