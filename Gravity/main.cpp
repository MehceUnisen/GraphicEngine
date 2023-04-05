#include "Gravity.h"
#include <iostream>
#include <thread>
int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Gravity");
	Gravity gravity(window, 1000);
	
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Time elapsed = clock.restart();
		
		window.clear();
		gravity.update(400.0f, elapsed);
		window.draw(gravity);
		window.display();
	
	}
}