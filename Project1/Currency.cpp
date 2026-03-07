#include "Currency.h"

#include "Player.h"

void Currency::onPickup(Player& player, std::unique_ptr<Item> self) {
    (void)self;
    player.addCurrencyFrom(*this);
}
