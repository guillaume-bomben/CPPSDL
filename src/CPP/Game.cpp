#include "Game.hpp"
#include <cstdlib>
#include <ctime>

Game::Game(Window &window) : window(window), running(true), gridSize(4) {
    srand(static_cast<unsigned>(time(nullptr)));
    initializeGrid();
    addRandomTile();
    addRandomTile();
}

Game::~Game() {}

void Game::initializeGrid() {
    grid = std::vector<std::vector<int>>(gridSize, std::vector<int>(gridSize, 0));
}

void Game::addRandomTile() {
    int value = (rand() % 2 + 1) * 2; // Génère 2 ou 4
    int x, y;
    do {
        x = rand() % gridSize;
        y = rand() % gridSize;
    } while (grid[x][y] != 0);

    grid[x][y] = value;
}

bool Game::move(int dx, int dy) {
    bool moved = false;
    // Logique de déplacement et fusion des tuiles
    // Retourner true si un déplacement a été effectué, sinon false
    return moved;
}

bool Game::canMove() const {
    // Logique pour vérifier s'il existe un mouvement possible
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            bool moved = false;
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:  moved = move(-1, 0); break;
                case SDLK_RIGHT: moved = move(1, 0); break;
                case SDLK_UP:    moved = move(0, -1); break;
                case SDLK_DOWN:  moved = move(0, 1); break;
            }
            if (moved) {
                addRandomTile();
                if (!canMove()) {
                    running = false; // Fin du jeu
                }
            }
        }
    }
}

void Game::update() {
    // Mise à jour de l'état du jeu si nécessaire
}

void Game::render() {
    window.clear();

    // Affichage des tuiles et de la grille
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] != 0) {
                Tile tile(grid[i][j], i, j);
                tile.render(window);
            }
        }
    }

    window.display();
}
