#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
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

static SDL_Surface* const background_sur = IMG_Load("images/background.jpg");

class SDL
{
public:
    static SDL_Surface* getSurface(int n){
        for (size_t i = 0; i < surfaces.size(); i++)
        {
            if (pow(2, i+1) == n){
                return surfaces[i];
            }
        }
        return NULL;
    };

    static void freeSurface(){
        for (size_t i = 0; i < surfaces.size(); i++)
        {
            SDL_FreeSurface(surfaces[i]);
        }
    }

    static void run(){
        SDL_Window* window = SDL_CreateWindow("First program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        Matrix matrix = Matrix();

        bool running = true;
        bool lose;

        SDL_Rect rects[4][4];
            for (size_t i = 0; i < 4; i++)
            {
                for (size_t j = 0; j < 4; j++)
                {
                    rects[i][j].w = 125;
                    rects[i][j].h = 125;
                    // SDL_QueryTexture(textures[0][0], NULL, NULL, &rects[i][j].w, &rects[i][j].h);
                    rects[i][j].x = 50 + (125*j); // 50 = 600 (window) - 500 (grille) / 2
                    rects[i][j].y = 50 + (125*i); // changer 50 si window != 600x600
                }
            }

        while (running) {
            SDL_Texture* textures[4][4];
            for (size_t i = 0; i < 4; i++)
            {
                for (size_t j = 0; j < 4; j++)
                {
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
            if (e.type == SDL_KEYDOWN){
                // keyboard API for key pressed
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_Z:
                    case SDL_SCANCODE_UP:
                        matrix.moveMatrix('u');
                        lose = !matrix.addNumber();
                        break;
                    case SDL_SCANCODE_Q:
                    case SDL_SCANCODE_LEFT:
                        matrix.moveMatrix('l');
                        lose = !matrix.addNumber();
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        matrix.moveMatrix('d');
                        lose = !matrix.addNumber();
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        matrix.moveMatrix('r');
                        lose = !matrix.addNumber();
                        break;
                }
            }

            if (lose){
                std::cout << "You lose";
                running = false;
            }

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, background_tex, NULL, NULL);
            for (size_t i = 0; i < 4; i++)
            {
                for (size_t j = 0; j < 4; j++)
                {
                    SDL_RenderCopy(renderer, textures[i][j], NULL, &rects[i][j]);
                }
                
            }
            SDL_RenderPresent(renderer);

            for (size_t i = 0; i < 4; i++)
            {
                for (size_t j = 0; j < 4; j++)
                {
                    SDL_DestroyTexture(textures[i][j]);
                }
            }
            SDL_DestroyTexture(background_tex);
        }

        

        freeSurface();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    };
};