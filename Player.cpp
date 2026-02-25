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
    if(!inventory.empty() && index < inventory.size()){
        unique_ptr<Item> tmp = move(inventory[index]);
        inventory.erase(inventory.begin() + index);
        if (inventory.empty()) {
            inventoryIdx = 0;
        } else if (inventoryIdx >= static_cast<int>(inventory.size())) {
            inventoryIdx = static_cast<int>(inventory.size()) - 1;
        }
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

bool Player::equipItem(bool equipLeftHand)
{
    if (inventory.empty() || inventoryIdx < 0 || inventoryIdx >= static_cast<int>(inventory.size())) {
        return false;
    }
    if (inventory[inventoryIdx] == nullptr || !inventory[inventoryIdx]->canEquip()) {
        return false;
    }

    if (inventory[inventoryIdx]->isTwoHanded()) {
        if (leftHand != nullptr || rightHand != nullptr) {
            return false;
        }
        leftHand = move(inventory[inventoryIdx]);
        inventory.erase(inventory.begin() + inventoryIdx);
        if (inventory.empty()) {
            inventoryIdx = 0;
        } else if (inventoryIdx >= static_cast<int>(inventory.size())) {
            inventoryIdx = static_cast<int>(inventory.size()) - 1;
        }
        return true;
    }

    if (leftHand != nullptr && leftHand->isTwoHanded()) {
        return false;
    }

    if (equipLeftHand && leftHand == nullptr) {
        leftHand = move(inventory[inventoryIdx]);
        inventory.erase(inventory.begin() + inventoryIdx);
        if (inventory.empty()) {
            inventoryIdx = 0;
        } else if (inventoryIdx >= static_cast<int>(inventory.size())) {
            inventoryIdx = static_cast<int>(inventory.size()) - 1;
        }
        return true;
    }
    if(!equipLeftHand && rightHand == nullptr) {
        rightHand = move(inventory[inventoryIdx]);
        inventory.erase(inventory.begin() + inventoryIdx);
        if (inventory.empty()) {
            inventoryIdx = 0;
        } else if (inventoryIdx >= static_cast<int>(inventory.size())) {
            inventoryIdx = static_cast<int>(inventory.size()) - 1;
        }
        return true;
    }
    return false;
}

bool Player::unequipItem(bool fromLeftHand)
{
    if (leftHand != nullptr && leftHand->isTwoHanded()) {
        inventory.push_back(move(leftHand));
        rightHand = nullptr;
        return true;
    }
    if (fromLeftHand && leftHand != nullptr) {
        inventory.push_back(move(leftHand));
        leftHand = nullptr;
        return true;
    }
    if (!fromLeftHand && rightHand != nullptr) {
        inventory.push_back(move(rightHand));
        rightHand = nullptr;
        return true;
    }
    return false;
}
