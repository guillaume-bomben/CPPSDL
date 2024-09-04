#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <cmath>
#include <conio.h>
#include "Matrix.hpp"

static std::vector<SDL_Surface*> const surfaces {
    IMG_Load("images/2.jpg"),
    IMG_Load("images/4.jpg"),
    IMG_Load("images/8.jpg"),
    IMG_Load("images/16.jpg"),
    IMG_Load("images/32.jpg"),
    IMG_Load("images/64.jpg"),
    IMG_Load("images/128.jpg"),
    IMG_Load("images/256.jpg"),
    IMG_Load("images/512.jpg"),
    IMG_Load("images/1024.jpg"),
    IMG_Load("images/2048.jpg"),
};

static SDL_Surface* const background_sur = IMG_Load("images/background.png");

class SDL
{
public:
    static SDL_Surface* getSurface(int n) {
        for (size_t i = 0; i < surfaces.size(); i++) {
            if (pow(2, i+1) == n) {
                return surfaces[i];
            }
        }
        return NULL;
    };

    static void freeSurface() {
        for (size_t i = 0; i < surfaces.size(); i++) {
            SDL_FreeSurface(surfaces[i]);
        }
    }

    static void run() {
        if (TTF_Init() == -1) {
            std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
            return;
        }

        // Initialisation de SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
            return;
        }

        // Charger le son de bruitage
        Mix_Chunk *SFX = Mix_LoadWAV("sounds/SFX.wav");
        if (SFX == NULL) {
            std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
            return;
        }

        SDL_Window* window = SDL_CreateWindow("First program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderSetLogicalSize(renderer, 800, 800);

        Matrix matrix = Matrix();

        TTF_Font* font = TTF_OpenFont("police/arial.ttf", 24);
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
            return;
        }

        bool running = true;
        bool lose;

        SDL_Rect rects[4][4];
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                rects[i][j].w = 125;
                rects[i][j].h = 125;
                rects[i][j].x = 160 + (125*j); 
                rects[i][j].y = 110 + (125*i); 
            }
        }

        while (running) {
            SDL_Texture* textures[4][4];
            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    textures[i][j] = SDL_CreateTextureFromSurface(renderer, getSurface(matrix.getElement(i, j)));
                }
            }

            SDL_Texture* background_tex = SDL_CreateTextureFromSurface(renderer, background_sur);

            SDL_Event e;

            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    break;
                }
            }
            if (e.type == SDL_KEYDOWN) {
                // Jouer le son à chaque appui de touche

                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_Z:
                    case SDL_SCANCODE_UP:
                        matrix.moveMatrix('u');
                        lose = !matrix.addNumber();
                        Mix_PlayChannel(-1, SFX, 0);

                        break;
                    case SDL_SCANCODE_Q:
                    case SDL_SCANCODE_LEFT:
                        matrix.moveMatrix('l');
                        lose = !matrix.addNumber();
                        Mix_PlayChannel(-1, SFX, 0);

                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        matrix.moveMatrix('d');
                        lose = !matrix.addNumber();
                        Mix_PlayChannel(-1, SFX, 0);
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        matrix.moveMatrix('r');
                        lose = !matrix.addNumber();
                        Mix_PlayChannel(-1, SFX, 0);
                        break;
                }
            }

            if (lose) {
                std::cout << "You lose";
                running = false;
            }

            // Calculer et afficher le score
            int score = matrix.getScore();
            SDL_Color textColor = { 255, 255, 255, 255 };
            std::string scoreText = "Score: " + std::to_string(score);
            SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
            SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
            SDL_Rect scoreRect = { 0, 0, scoreSurface->w, scoreSurface->h };

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, background_tex, NULL, NULL);
            SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect); // Afficher le score

            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    SDL_RenderCopy(renderer, textures[i][j], NULL, &rects[i][j]);
                }
            }
            SDL_RenderPresent(renderer);

            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++) {
                    SDL_DestroyTexture(textures[i][j]);
                }
            }
            SDL_DestroyTexture(scoreTexture);
            SDL_FreeSurface(scoreSurface);
            SDL_DestroyTexture(background_tex);
        }

        // Libérer les ressources sonores
        Mix_FreeChunk(SFX);
        Mix_CloseAudio();

        freeSurface();
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    };
};
