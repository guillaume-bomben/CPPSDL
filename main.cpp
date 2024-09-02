#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <iostream>
#include <cmath>

static std::vector<SDL_Surface*> const surfaces {
    IMG_Load("2 Tile.png"),
    IMG_Load("4 Tile.png"),
    IMG_Load("8 Tile.png"),
    IMG_Load("16 Tile.png"),
    IMG_Load("32 Tile.png"),
    IMG_Load("64 Tile.png"),
    IMG_Load("128 Tile.png"),
    IMG_Load("256 Tile.png"),
    IMG_Load("512 Tile.png"),
    IMG_Load("1024 Tile.png"),
    IMG_Load("2048 Tile.png"),
};

static SDL_Surface* getSurface(int num){
    for (size_t i = 0; i < surfaces.size(); i++)
    {
        if(pow(2, i+1) == num){
            return surfaces[i];
        }
    }
    return NULL;
}

class Tile
{
private:
    SDL_Texture* tex;
public:
    Tile(SDL_Renderer* rend);
    ~Tile();
    SDL_Texture* getTexture();
};

Tile::Tile(SDL_Renderer* rend)
{
    if (rand()%10 < 8){
        tex = SDL_CreateTextureFromSurface(rend, getSurface(2));
    }
    else{
        tex = SDL_CreateTextureFromSurface(rend, getSurface(4));
    }
}

Tile::~Tile()
{
}

SDL_Texture* Tile::getTexture(){
    return tex;
}

 
int main(int argc, char *argv[])
{
    SDL_Window* win = SDL_CreateWindow("2048", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       500, 500, 0);
 
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // creates a surface to load an image into the main memory
    Tile t = Tile(rend);

    Tile* matrix[4][4];
 
    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;

    // List of Rect to move all rects at once later
    std::vector<SDL_Rect> rects;
    rects.insert(rects.end(), dest);
 
    // connects our texture with dest to control position
    SDL_QueryTexture(t.getTexture(), NULL, NULL, &rects[0].w, &rects[0].h);
 
    // sets initial x-position of object
    rects[0].x = 0;
 
    // sets initial y-position of object
    rects[0].y = 0;

    matrix[0][0] = &t;
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    int speed = 300;
 
    // animation loop
    while (!close) {
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
 
            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    std::cout << rects[0].y << std::endl;
                    for (size_t i = 0; i < rects.size(); i++)
                    {
                        rects[i].y -= 125;
                        if (rects[i].y < 0)
                            rects[i].y = 0;
                    }
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    std::cout << rects[0].x << std::endl;
                    for (size_t i = 0; i < rects.size(); i++)
                    {
                        rects[i].x -= 125;
                        if (rects[i].x < 0)
                            rects[i].x = 0;
                    }
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    std::cout << rects[0].y << std::endl;
                    for (size_t i = 0; i < rects.size(); i++)
                    {
                        rects[i].y += 125;
                        if (rects[i].y + rects[i].h > 500)
                            rects[i].y = 500 - rects[i].h;
                    }
                    dest.y += 125;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    std::cout << rects[0].x << std::endl;
                    for (size_t i = 0; i < rects.size(); i++)
                    {
                        rects[i].x += 125;
                        if (rects[i].x + rects[i].w > 500)
                            rects[i].x = 500 - rects[i].w;
                    }
                    dest.x += 125;
                    break;
                default:
                    break;
                }
                bool origin = false;
                for (size_t i = 0; i < rects.size(); i++)
                {
                    if (rects[i].x == 0 && rects[i].y == 0){
                        origin = true;
                    }
                }
                if (!origin){

                }
            }
        }
 
        // clears the screen
        SDL_RenderClear(rend);
        for (size_t i = 0; i < rects.size(); i++)
        {
            SDL_RenderCopy(rend, t.getTexture(), NULL, &rects[i]);
        }
 
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy texture
    SDL_DestroyTexture(t.getTexture());
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}