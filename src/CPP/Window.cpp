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