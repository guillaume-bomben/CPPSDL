#include "../HPP/GameObject.hpp"
#include <iostream>

GameObject::GameObject(){}

GameObject::GameObject(int x, int y, int width, int height, const std::string& texturePath) : x{x}, y{y}, width{width}, height{height}{
    this->TextureImage.loadFromFile(texturePath);
    this->sprite.setTexture(this->TextureImage);
    this->sprite.setPosition(this->x, this->y);
}

GameObject::~GameObject(){}

int GameObject::getX(){
    return this->x;
}

int GameObject::getY(){
    return this->y;
}

void GameObject::setX(int x){
    this->x = x;
}

void GameObject::setY(int y){
    this->y = y;
}

void GameObject::setTextureImage(const std::string& texturePath){
    this->TextureImage.loadFromFile(texturePath);
    this->setSprite();
}

void GameObject::setSprite(){
    this->sprite.setTexture(this->TextureImage);
    this->sprite.setPosition(this->x, this->y);
}

sf::Sprite GameObject::getSprite(){
    return this->sprite;
}
