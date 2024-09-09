#include <SFML/Graphics.hpp>

class GameObject{
    protected:
        int x, y;
        int width, height;
        sf::Texture texture;
        sf::Sprite sprite;

    public:
        GameObject(int x, int y, int width, int height, const std::string& texturePath);
        virtual ~GameObject();

        int getX();
        int getY();
        void setX(int x);
        void setY(int y);

        void setTexture(const std::string& texturePath);
        void setSprite();
        sf::Sprite getSprite();
};