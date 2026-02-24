#include "World.h"
#include "Weapon.h"
using namespace std;



World::World(){
    for(int i = 0; i < Rows; i++){
        grid.push_back(vector<Tile>(Cols));
        for(int j = 0; j < Cols; j++){
            if(i == 0 || j == 0 || j == Cols-1 || i == Rows-1){
                grid[i][j] = Tile(true);
            }
            else{
                grid[i][j] = Tile(false);
            }
        }
    }
    grid[10][2].addItem(make_unique<Item>("axe", 'p'));
    grid[3][27].addItem(make_unique<Item>("aa", 'p'));
    grid[6][12].addItem(make_unique<Item>("aaaxe", 'p'));
    grid[10][2].addItem(make_unique<Item>("sseaw", 'p'));
    grid[10][20].addItem(make_unique<Item>("sseaw", 'p'));
    grid[10][20].addItem(make_unique<Item>("sseaw", 'p'));
    grid[10][20].addItem(make_unique<Item>("sseaw", 'p'));
    grid[10][20].addItem(make_unique<Weapon>("Steel Sword", '/', 12, false));

}