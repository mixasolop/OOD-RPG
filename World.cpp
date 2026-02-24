#include "World.h"

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
}