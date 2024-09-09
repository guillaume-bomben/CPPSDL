#include <SFML/Graphics.hpp>

class Window{ 
    private:
        unsigned int width;
        unsigned int height;
    
    public:
        Window(unsigned int width, unsigned int height) : width{width}, height{height} {}
        ~Window();
        void run();
};