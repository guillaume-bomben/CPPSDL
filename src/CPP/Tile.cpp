#include "../HPP/Tile.hpp"

Tile::Tile(int x, int y, int width, int height, int value)
    : GameObject(x, y, width, height, "images/" + std::to_string(value) + ".jpg"), value(value){
    this->TexturePath = "images/" + std::to_string(value) + ".jpg";
}

Tile::~Tile(){
    GameObject::~GameObject();
}

int Tile::getValue(){
    return this->value;
}

void Tile::setValue(int value){
    this->value = value;
    this->TexturePath = "images/" + std::to_string(value) + ".jpg";
    this->setTexture(TexturePath);
}



