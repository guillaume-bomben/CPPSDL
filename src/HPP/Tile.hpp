#ifndef TILE_HPP
#define TILE_HPP

#include "GameObject.hpp"

class Tile : public GameObject{
    private:
        int value;
        std::string TexturePath;
    
    public:
        Tile();
        Tile(int x, int y, int width, int height, int value);
        ~Tile();
        int getValue();
        void setValue(int value);
        std::string getTexturePath();
};

#endif