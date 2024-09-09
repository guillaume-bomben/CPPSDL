#include "../HPP/Window.hpp"

Window::~Window(){
    // Destructor
}

void Window::run(){
    auto window = sf::RenderWindow{ { this->width, this->height }, "2048" };
    window.setFramerateLimit(60);

    while (window.isOpen()){
        for (auto event = sf::Event{}; window.pollEvent(event);){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
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