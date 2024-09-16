#include "../HPP/Window.hpp"
#include "../HPP/Game.hpp"
#include "../HPP/Tile.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Window::~Window(){
    // Destructor
}

void Window::run(){
    bool loose = false;
    this->backTexture.loadFromFile("images/background.png");
    this->backSprite.setTexture(this->backTexture);

    sf::Font font;
    if (!font.loadFromFile("Font/Arial.ttf")){
        std::cout << "Error loading font" << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("You loose, Press R to restart");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(200, 200);

    auto window = sf::RenderWindow{ { this->width, this->height }, "2048" };
    window.setFramerateLimit(60);
    Game game = Game();
    Tile tile = Tile();

    while (window.isOpen()){
        sf::sleep(sf::milliseconds(100));
        for (auto event = sf::Event{}; window.pollEvent(event);){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == event.KeyPressed){
                if (event.key.code == sf::Keyboard::Up){
                    game.matrix.moveMatrix('u');
                    loose = !game.matrix.addNumber();
                    game.update();
                }
                else if (event.key.code == sf::Keyboard::Down){
                    game.matrix.moveMatrix('d');
                    loose = !game.matrix.addNumber();
                    game.update();
                }
                else if (event.key.code == sf::Keyboard::Left){
                    game.matrix.moveMatrix('l');
                    loose = !game.matrix.addNumber();
                    game.update();
                }
                else if (event.key.code == sf::Keyboard::Right){
                    game.matrix.moveMatrix('r');
                    loose = !game.matrix.addNumber();
                    game.update();
                }
                else if (event.key.code == sf::Keyboard::R){
                    game = Game();
                    loose = false;
                }
            }
        }

        window.clear();

        if (loose){
            //window.close();
            window.draw(text);
        }
        else{
            window.draw(this->backSprite);

            for (size_t i = 0; i < game.tiles.size(); ++i) {
                tile = game.tiles[i];
                tile.setTextureImage(game.tiles[i].getTexturePath());
                window.draw(tile.getSprite());
            }
        }

        
        

        window.display();
    }
}

unsigned int Window::getWidth(){
    return this->width;
}

unsigned int Window::getHeight(){
    return this->height;
}

void Window::setWidth(unsigned int width){
    this->width = width;
}

void Window::setHeight(unsigned int height){
    this->height = height;
}