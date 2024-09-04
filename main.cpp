#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Game.hpp"
#include "Window.hpp"

int main(int argc, char* argv[]) {
    Window window("2048 Game", 600, 600);
    Game game(window);

    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    return 0;
}
