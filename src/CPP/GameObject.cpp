#include "../HPP/GameObject.hpp"

GameObject::GameObject(int x, int y, int width, int height, const std::string& texturePath) : x{x}, y{y}, width{width}, height{height}{
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->x, this->y);
    
}

GameObject::~GameObject(){
    this->texture.~Texture();
}

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

void GameObject::setTexture(const std::string& texturePath){
    this->texture.loadFromFile(texturePath);
    GameObject::setSprite();
}

void GameObject::setSprite(){
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->x, this->y);
}

sf::Sprite GameObject::getSprite(){
    return this->sprite;
}
