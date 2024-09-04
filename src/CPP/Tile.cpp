#include "Tile.hpp"

Tile::Tile(int value, int gridX, int gridY) : value(value) {
    x = gridX * 100 + 10;
    y = gridY * 100 + 10;
    width = 80;
    height = 80;
}

SDL_Color Tile::getColor() const {
    switch (value) {
        case 2: return {238, 228, 218, 255};
        case 4: return {237, 224, 200, 255};
        // Ajout d'autres cas pour d'autres valeurs
        default: return {205, 193, 180, 255};
    }
}

void Tile::render(Window &window) {
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(window.getRenderer(), getColor().r, getColor().g, getColor().b, 255);
    SDL_RenderFillRect(window.getRenderer(), &rect);
    // Ajout du texte pour la valeur si nécessaire
}
