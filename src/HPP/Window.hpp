#pragma once
#include <SDL2/SDL.h>
#include <string>

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    void clear();
    void display();
    SDL_Renderer* getRenderer() const { return renderer; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
