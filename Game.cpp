#include "Game.h"

using namespace std;

Game::Game(){}

void Game::render(){
    renderer.draw(world, player);
}

void Game::run(){
    running = true;

    while(running){
        render();
    }
}


