#include "Player.h"

using namespace std;

class World;

Player::Player(){
    row = 0 ;
    col = 0;

    stats.strength = 5;
    stats.dexterity = 5;
    stats.health = 100;
    stats.luck = 5;
    stats.aggression = 5;
    stats.wisdom = 5;

    coins = 0;
    gold = 0;
}

const Player::Attributes& Player::getAttributes() const{
    return stats;
}

vector<unique_ptr<Item>>& Player::getInventory(){
    return inventory;
}

unique_ptr<Item> Player::dropItem(size_t index)
{
    if(!inventory.empty()){
        unique_ptr<Item> tmp = move(inventory[index]);
        inventory.erase(inventory.begin() + index);
        return tmp;
    }
    return nullptr;
}

void Player::moveInventory(bool Up)
{
    if (inventory.empty()) {
        inventoryIdx = 0;
        return;
    }
    if (Up && inventoryIdx > 0) {
        inventoryIdx--;
    }
    else if (!Up && inventoryIdx < static_cast<int>(inventory.size())-1) {
        inventoryIdx++;
    }
}
