#include "Collision.hpp"

Collision::Collision() : 
	m_vertices(sf::Quads, 8),
	m_quadLen(50.0f),
	m_quadOrigin(2),
	m_selectedQuad(0)
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 800), "Collision");
	
	m_quadOrigin.at(0) = sf::Vector2f(400.0f, 400.0f);
	m_quadOrigin.at(1) = sf::Vector2f(225.0f, 75.0f);
	
	while (m_window->isOpen()) {
		sf::Event event;
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window->close();
			}
		}

		m_window->clear();

		takeInput();
		renderVertices();

		m_window->draw(m_vertices);
		m_window->display();
	}
}

void Collision::renderVertices() { 
	renderQuad(sf::Vector2f(m_quadOrigin.at(0).x - m_quadLen / 2, m_quadOrigin.at(0).y - m_quadLen / 2), m_quadLen, 0);
	renderQuad(sf::Vector2f(m_quadOrigin.at(1).x - m_quadLen / 2, m_quadOrigin.at(1).y - m_quadLen / 2), m_quadLen, 4);
}

void Collision::renderQuad(sf::Vector2f coord, float quadLen, std::size_t index) {
	
	m_vertices[index].position = sf::Vector2f(coord.x, coord.y);
	m_vertices[index + 1].position = sf::Vector2f(coord.x + m_quadLen, coord.y);
	m_vertices[index + 2].position = sf::Vector2f(coord.x + m_quadLen, coord.y + m_quadLen);
	m_vertices[index + 3].position = sf::Vector2f(coord.x, coord.y + m_quadLen); 
}

void Collision::takeInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		m_selectedQuad = (m_selectedQuad == 0) ? 1 : 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	{
		move(m_selectedQuad, sf::Vector2f(-.1f, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		move(m_selectedQuad, sf::Vector2f(.1f, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		move(m_selectedQuad, sf::Vector2f(.0f, -.1f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		move(m_selectedQuad, sf::Vector2f(.0f, .1f));
	}
}

void Collision::move(std::size_t index, sf::Vector2f coord) {
	
	m_quadOrigin.at(index).x += coord.x / 2;
	m_quadOrigin.at(index).y += coord.y / 2;
}