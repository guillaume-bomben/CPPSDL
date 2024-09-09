#include <SFML/Graphics.hpp>

class Window{ 
    private:
        unsigned int width;
        unsigned int height;
        sf::Texture backTexture;
        sf::Sprite backSprite;
    
    public:
        Window(unsigned int width, unsigned int height) : width{width}, height{height} {}
        ~Window();
        void run();
        unsigned int getWidth();
        unsigned int getHeight();
        void setWidth(unsigned int width);
        void setHeight(unsigned int height);
};