#pragma once

#include "Player.h"
#include "Renderer.h"
#include "World.h"
#include <iostream>
using namespace std;


class Game {
private:
    World world;
    Player player;
    Renderer renderer;
    bool running;

public:
    Game();
    void run();

private:
    void handleInput(char key);
    void render();
};