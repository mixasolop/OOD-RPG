#include "World.h"
#include "Weapon.h"
#include "MiscItem.h"
#include "Currency.h"
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

    auto hPotion = make_unique<MiscItem>("Health Potion", '-H');
    auto sPotion = make_unique<MiscItem>("Speed Potion", '-S');
    auto dPotion = make_unique<MiscItem>("Damage Potion", '-D');
    auto uHorn = make_unique<MiscItem>("Unicorn Horn", '-/');

    grid[3][27].addItem(move(hPotion));
    grid[6][12].addItem(move(hPotion));
    grid[10][2].addItem(move(dPotion));
    grid[10][20].addItem(move(dPotion));
    grid[10][20].addItem(move(sPotion));
    grid[10][20].addItem(move(uHorn));


    auto sword = make_unique<Weapon>("Steel Sword", '/', 12, false);
    auto axe = make_unique<Weapon>("Wooden double Axe", 'P', 20, true);
    auto bow = make_unique<Weapon>("Wooden Bow", 'D', 10, true);
    auto knife = make_unique<Weapon>("Kitchen knife", 'i', 7, false);
    grid[0][2].addItem(move(sword));
    grid[10][20].addItem(move(axe));
    grid[10][20].addItem(move(bow));
    grid[1][0].addItem(move(knife));

    auto coin = make_unique<Currency>("Coins", 'c', 15, false);
    auto gole = make_unique<Currency>("Gold", '$', 3, true);
    grid[4][6].addItem(move(coin));
    grid[9][18].addItem(move(gole));

    grid[0][0].setWall(false);
    grid[0][1].setWall(false);
    grid[2][0].setWall(false);
    grid[1][0].setWall(false);
    grid[0][2].setWall(false);

}