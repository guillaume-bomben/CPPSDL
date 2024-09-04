#pragma once
#include "Window.hpp"
#include "Tile.hpp"
#include <vector>

class Game {
public:
    Game(Window &window);
    ~Game();

    void handleEvents();
    void update();
    void render();
    bool isRunning() const { return running; }

private:
    void initializeGrid();
    void addRandomTile();
    bool move(int dx, int dy);
    bool canMove() const;

    Window& window;
    std::vector<std::vector<int>> grid;
    bool running;
    int gridSize;
};
