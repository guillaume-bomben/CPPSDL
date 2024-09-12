#ifndef GAME_H
#define GAME_H

#include "Matrix.hpp"
#include "Tile.hpp"
#include <vector>

class Game : public Matrix{
    
    public:
        Matrix matrix = Matrix();
        std::vector<Tile> tiles;
        Game();
        ~Game();
        void update();
        void createTile();

};

#endif