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
		isColliding();
		m_window->draw(m_vertices);
		m_window->display();
	}
}

void Collision::renderVertices() { 
	renderQuad(sf::Vector2f(m_quadOrigin.at(0).x - m_quadLen / 2, m_quadOrigin.at(0).y - m_quadLen / 2), m_quadLen, 0);
	renderQuad(sf::Vector2f(m_quadOrigin.at(1).x - m_quadLen / 2, m_quadOrigin.at(1).y - m_quadLen / 2), m_quadLen, 1);
}

void Collision::renderQuad(sf::Vector2f coord, float quadLen, std::size_t index) {
	index *= 4;
	m_vertices[index].position = sf::Vector2f(coord.x, coord.y);
	m_vertices[index + 1].position = sf::Vector2f(coord.x + m_quadLen, coord.y);
	m_vertices[index + 2].position = sf::Vector2f(coord.x + m_quadLen, coord.y + m_quadLen);
	m_vertices[index + 3].position = sf::Vector2f(coord.x, coord.y + m_quadLen); 
}

void Collision::changeQuadColor(std::size_t index, sf::Color color) {
	index *= 4;
	m_vertices[index].color = color;
	m_vertices[index + 1].color = color;
	m_vertices[index + 2].color = color;
	m_vertices[index + 3].color = color;
}

bool Collision::isOutOfBounds(sf::Vector2f coord) {
	if (coord.x <= m_quadLen / 2 || coord.y <= m_quadLen / 2) {
		return false;
	}
	else if (coord.x >= 800.0f - m_quadLen / 2 || coord.y >= 800.0f - m_quadLen / 2) {
		return false;
	}
	else {
		return true;
	}
}

void Collision::takeInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		changeQuadColor(m_selectedQuad, sf::Color::White);
		m_selectedQuad = (m_selectedQuad == 0) ? 1 : 0;
		changeQuadColor(m_selectedQuad, sf::Color::Red);
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
	sf::Vector2f tempCoords = m_quadOrigin.at(index);
	tempCoords.x += coord.x / 2;
	tempCoords.y += coord.y / 2;
	
	if (isOutOfBounds(tempCoords)) {
		m_quadOrigin.at(index).x += coord.x / 2;
		m_quadOrigin.at(index).y += coord.y / 2;
	}
}

sf::Vector2f Collision::normal(sf::Vector2f coord) {
	return sf::Vector2f(-coord.y, coord.x);
}

std::array<sf::Vector2f, 4> Collision::getSeparatingAxes(std::size_t index) {
	std::array<sf::Vector2f, 4> axes;
	index *= 4;
	for (size_t i = 0; i < 4; i++)
	{
		sf::Vector2f p1 = m_vertices[index + i].position;
		sf::Vector2f p2 = m_vertices[index + i + 1].position;
		axes[i] = normal(sf::Vector2f(p1.x - p2.x, p1.y - p2.y));
	}
	return axes;
}

float Collision::dotProduct(sf::Vector2f p1, sf::Vector2f p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

std::array<float, 2> Collision::project(sf::Vector2f axis, std::size_t index) {
	index *= 4;
	float min = dotProduct(axis, m_vertices[index].position);
	float max = min;
	
	for (int i = 0; i < 4; i++)
	{
		float p = dotProduct(axis, m_vertices[index + i].position);
		if (p < min)
		{
			min = p;
		}
		else if (max < p)
		{
			max = p;
		}
	}
	return std::array<float, 2> {min, max};
}

bool Collision::isOverlapping(std::array<float, 2> p1, std::array<float, 2> p2) {
	if (abs(p1[0]) > abs(p2[0]) && abs(p1[0]) < abs(p2[1]))
	{
		return true;
	}
	else if (abs(p1[1]) > abs(p2[1]) && abs(p1[1]) < abs(p2[0])) {
		return true;
	}
	else if (abs(p2[0]) > abs(p1[0]) && abs(p2[0]) < abs(p1[1]))
	{
		return true;
	}
	else if (abs(p2[1]) > abs(p1[1]) && abs(p2[1]) < abs(p1[0])) {
		return true;
	}
	return false;
}

bool Collision::isColliding() {
	std::array<sf::Vector2f, 4> axes1 = getSeparatingAxes(0);
	std::array<sf::Vector2f, 4> axes2 = getSeparatingAxes(1);
	for (size_t i = 0; i < 4; i++)
	{
		sf::Vector2f axis = axes1[i];
		std::array<float, 2> p1 = project(axis, 0);
		std::array<float, 2> p2 = project(axis, 1);

		if (!isOverlapping(p1, p2))
		{
			return false;
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		sf::Vector2f axis = axes2[i];
		std::array<float, 2> p1 = project(axis, 0);
		std::array<float, 2> p2 = project(axis, 1);

		if (!isOverlapping(p1, p2))
		{
			return false;
		}
	}
	std::cout << "COLLIDING\n";
	return true;
}