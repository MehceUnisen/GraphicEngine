#include "ParticleHandler.h"
#include <iostream>
int main() {
	ParticleHandler particleHandler;
	
	particleHandler.appendParticle(Particle(sf::Vector2f(150.0f, 150.0f)));
	particleHandler.appendParticle(Particle(sf::Vector2f(150.0f, 200.0f)));
	particleHandler.appendParticle(Particle(sf::Vector2f(200.0f, 200.0f)));
	particleHandler.appendParticle(Particle(sf::Vector2f(200.0f, 150.0f)));
	
	particleHandler.at(0).color = sf::Color::White;
	particleHandler.at(1).color = sf::Color::White;
	particleHandler.at(2).color = sf::Color::White;
	particleHandler.at(3).color = sf::Color::White;

	sf::RenderWindow window(sf::VideoMode(800, 800), "test");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(particleHandler.at(0));
		window.draw(particleHandler.at(1));
		window.draw(particleHandler.at(2));
		window.draw(particleHandler.at(3));
		window.display();
	}
}