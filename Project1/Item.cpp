#include "Item.h"

#include <utility>

#include "Player.h"

void Item::onPickup(Player& player, unique_ptr<Item> self) {
    player.pickUp(std::move(self));
}
