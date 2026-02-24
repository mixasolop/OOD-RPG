#include "Player.h"

using namespace std;


Player::Player(){
    row = 0;
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
