#include <SFML/Graphics.hpp>

class Window{ 
    public:
        static void run(){
            auto window = sf::RenderWindow{ { 800, 800 }, "2048" };
            window.setFramerateLimit(60);

            while (window.isOpen())
            {
                for (auto event = sf::Event{}; window.pollEvent(event);)
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                }

                window.clear();
                window.display();
            }
        }
};