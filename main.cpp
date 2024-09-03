#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

static std::vector<SDL_Surface*> const surfaces {
    IMG_Load("images/2 Tile.png"),
    IMG_Load("images/4 Tile.png"),
    IMG_Load("images/8 Tile.png"),
    IMG_Load("images/16 Tile.png"),
    IMG_Load("images/32 Tile.png"),
    IMG_Load("images/64 Tile.png"),
    IMG_Load("images/128 Tile.png"),
    IMG_Load("images/256 Tile.png"),
    IMG_Load("images/512 Tile.png"),
    IMG_Load("images/1024 Tile.png"),
    IMG_Load("images/2048 Tile.png"),
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

void moveMatrix(char d[], int n, int a[4][4])
{
 
    // For right shift move.
    if (d[0] == 'r') {
 
        // for each row from
        // top to bottom
        for (int i = 0; i < n; i++) {
            std::vector<int> v, w;
            int j;
 
            // for each element of
            // row from right to left
            for (j = n - 1; j >= 0; j--) {
                // if not 0
                if (a[i][j])
                    v.push_back(a[i][j]);
            }
 
            // for each temporary array
            for (j = 0; j < v.size(); j++) {
                // if two element have same
                // value at consecutive position.
                if (j < v.size() - 1 && v[j] == v[j + 1]) {
                    // insert only one element
                    // as sum of two same element.
                    w.push_back(2 * v[j]);
                    j++;
                }
                else
                    w.push_back(v[j]);
            }
 
            // filling the each row element to 0.
            for (j = 0; j < n; j++)
                a[i][j] = 0;
 
            j = n - 1;
 
            // Copying the temporary
            // array to the current row.
            for (auto it = w.begin();
                 it != w.end(); it++)
                a[i][j--] = *it;
        }
    }
 
    // for left shift move
    else if (d[0] == 'l') {
 
        // for each row
        for (int i = 0; i < n; i++) {
            std::vector<int> v, w;
            int j;
 
            // for each element of the
            // row from left to right
            for (j = 0; j < n; j++) {
                // if not 0
                if (a[i][j])
                    v.push_back(a[i][j]);
            }
 
            // for each temporary array
            for (j = 0; j < v.size(); j++) {
                // if two element have same
                // value at consecutive position.
                if (j < v.size() - 1 && v[j] == v[j + 1]) {
                    // insert only one element
                    // as sum of two same element.
                    w.push_back(2 * v[j]);
                    j++;
                }
                else
                    w.push_back(v[j]);
            }
 
            // filling the each row element to 0.
            for (j = 0; j < n; j++)
                a[i][j] = 0;
 
            j = 0;
 
            for (auto it = w.begin();
                 it != w.end(); it++)
                a[i][j++] = *it;
        }
    }
 
    // for down shift move.
    else if (d[0] == 'd') {
        // for each column
        for (int i = 0; i < n; i++) {
            std::vector<int> v, w;
            int j;
 
            // for each element of
            // column from bottom to top
            for (j = n - 1; j >= 0; j--) {
                // if not 0
                if (a[j][i])
                    v.push_back(a[j][i]);
            }
 
            // for each temporary array
            for (j = 0; j < v.size(); j++) {
 
                // if two element have same
                // value at consecutive position.
                if (j < v.size() - 1 && v[j] == v[j + 1]) {
                    // insert only one element
                    // as sum of two same element.
                    w.push_back(2 * v[j]);
                    j++;
                }
                else
                    w.push_back(v[j]);
            }
 
            // filling the each column element to 0.
            for (j = 0; j < n; j++)
                a[j][i] = 0;
 
            j = n - 1;
 
            // Copying the temporary array
            // to the current column
            for (auto it = w.begin();
                 it != w.end(); it++)
                a[j--][i] = *it;
        }
    }
 
    // for up shift move
    else if (d[0] == 'u') {
        // for each column
        for (int i = 0; i < n; i++) {
            std::vector<int> v, w;
            int j;
 
            // for each element of column
            // from top to bottom
            for (j = 0; j < n; j++) {
                // if not 0
                if (a[j][i])
                    v.push_back(a[j][i]);
            }
 
            // for each temporary array
            for (j = 0; j < v.size(); j++) {
                // if two element have same
                // value at consecutive position.
                if (j < v.size() - 1 && v[j] == v[j + 1]) {
                    // insert only one element
                    // as sum of two same element.
                    w.push_back(2 * v[j]);
                    j++;
                }
                else
                    w.push_back(v[j]);
            }
 
            // filling the each column element to 0.
            for (j = 0; j < n; j++)
                a[j][i] = 0;
 
            j = 0;
 
            // Copying the temporary array
            // to the current column
            for (auto it = w.begin();
                 it != w.end(); it++)
                a[j++][i] = *it;
        }
    }
}

bool addNumber(int matrix[4][4]){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (matrix[i][j] == 0){
                matrix[i][j] = rand()%10<8 ? 2 : 4;
                return true;
            }
        }
    }
    return false;
}

void Console(){
    int matrix[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }

    matrix[0][0] = 2;

    bool running = true;

    while(running){
        std::cout << "2048 :\n" << std::endl;
        std::cout << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << " " << matrix[0][3] << std::endl;
        std::cout << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << " " << matrix[1][3] << std::endl;
        std::cout << matrix[2][0] << " " << matrix[2][1] << " " << matrix[2][2] << " " << matrix[2][3] << std::endl;
        std::cout << matrix[3][0] << " " << matrix[3][1] << " " << matrix[3][2] << " " << matrix[3][3] << std::endl << std::endl;

        std::string s = "";
        while (s != "N" && s != "E" & s != "S" & s != "W" & s != "Q"){
            std::cout << "Choose a direction (N, E, S, W) (Q = Quit) : " << std::endl;
            std::cin >> s;
        }
        if (s == "N"){
            moveMatrix("u", 4, matrix);
            addNumber(matrix);
        }
        else if (s == "E"){
            moveMatrix("r", 4, matrix);
            addNumber(matrix);
        }
        else if (s == "S"){
            moveMatrix("d", 4, matrix);
            addNumber(matrix);
        }
        else if (s == "W"){
            moveMatrix("l", 4, matrix);
            addNumber(matrix);
        }
        else if (s == "Q"){
            running = false;
        }
    }
}

void SDL()
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
}

int main(int argc, char *argv[])
{
    Console();
    // SDL();

    return 0;
}
