#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject{
    protected:
        int x, y;
        int width, height;
        sf::Texture TextureImage;
        sf::Sprite sprite;

    public:
        GameObject();
        GameObject(int x, int y, int width, int height, const std::string& texturePath);
        virtual ~GameObject();

        int getX();
        int getY();
        void setX(int x);
        void setY(int y);

        void setTextureImage(const std::string& texturePath);
        void setSprite();
        sf::Sprite getSprite();
};

#endif