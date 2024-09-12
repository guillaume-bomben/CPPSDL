#include "../HPP/Game.hpp"
#include "../HPP/Tile.hpp"


Game::Game(){
    this->createTile();
}

Game::~Game(){
    // Destructor
}

void Game::update(){
    tiles.clear();
    this->createTile();
}

void Game::createTile(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (matrix.matrix[i][j] != 0){
                Tile tile = Tile(168 + (125*j), 120 + (125*i) , 125, 125, matrix.matrix[i][j]);
                tiles.push_back(tile);
            }   
        }
    }
}