#include "GameObject.hpp"

class Tile : public GameObject{
    private:
        int value;
        std::string TexturePath;
    
    public:
        Tile(int x, int y, int width, int height, int value);
        ~Tile();
        int getValue();
        void setValue(int value);
};