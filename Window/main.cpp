#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Map");

    sf::CircleShape circle(200.0f);
    circle.setFillColor(sf::Color(31, 31, 31));

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::Blue);

        window.draw(circle);

        window.display();
    }

    return 0;
}