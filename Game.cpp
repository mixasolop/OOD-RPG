#include "Game.h"

using namespace std;
#include <conio.h>

Game::Game(){
    player.setPosition(world.getRows()/2, world.getCols()/2);
}

void Game::handleInput(char key)
{
    switch (key)
    {
    case '.':
        running = 0;
        break;
    case 'w':
        if (!world.isWalkable(player.getRow()-1, player.getCol())) {
            break;
        }
        player.setPosition(player.getRow()-1, player.getCol());
        break;
    case 'a':
        if (!world.isWalkable(player.getRow(), player.getCol() - 1)) {
            break;
        }
        player.setPosition(player.getRow(), player.getCol() - 1);
        break;
    case 's':
        if (!world.isWalkable(player.getRow()+1, player.getCol())) {
            break;
        }
        player.setPosition(player.getRow()+1, player.getCol());
        break;
    case 'd':
        if (!world.isWalkable(player.getRow(), player.getCol() + 1)) {
            break;
        }
        player.setPosition(player.getRow(), player.getCol() + 1);
        break;
    case 'e':
        if (world.at(player.getRow(), player.getCol()).hasItems()) {
            player.pickUp(world.at(player.getRow(), player.getCol()).takeItem(0));
        }
        break;
    case '-':
    case '_':
        player.moveInventory(true);
        break;
    case '=':
        player.moveInventory(false);
        break;
    case 'q':
        {
            unique_ptr<Item> dropped = player.dropItem(player.getInvIdx());
            if (dropped != nullptr) {
                world.at(player.getRow(), player.getCol()).addItem(move(dropped));
                player.moveInventory(true);
            }
        }
        break;
    case 'l':
        if (player.equipItem(true) == false) {
            player.unequipItem(true);
            break;
        }
        break;
    case 'k':
        if (player.equipItem(false) == false) {
            player.unequipItem(false);
            break;
        }
        break;
    default:
        break;
    }
}

void Game::render(){
    renderer.draw(world, player);
}

void Game::run(){
    running = true;
    render();
    while (running) {
        char key = static_cast<char>(_getch());
        handleInput(key);
        render();
    }
}


