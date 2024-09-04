#pragma once
#include "GameObject.hpp"

class Tile : public GameObject {
public:
    Tile(int value, int gridX, int gridY);
    void render(Window &window) override;

private:
    int value;
    SDL_Color getColor() const;
};
