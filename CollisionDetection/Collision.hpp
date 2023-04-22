#include <SFML/Graphics.hpp>
#include <thread>
#include <array>
#include <iostream>
#include <math.h>

class Collision {

public:
	Collision();

private:
	
	void renderVertices();
	void renderQuad(sf::Vector2f coord, float quadLen, std::size_t index);
	void changeQuadColor(std::size_t index, sf::Color color);

	void takeInput();
	void move(std::size_t index, sf::Vector2f coord);
	bool isOutOfBounds(sf::Vector2f coord);

	sf::Vector2f normal(sf::Vector2f coord);
	std::array<sf::Vector2f, 4> getSeparatingAxes(std::size_t index);
	
	float dotProduct(sf::Vector2f p1, sf::Vector2f p2);
	std::array<float,2> project(sf::Vector2f axis, std::size_t index);
	
	bool isOverlapping(std::array<float, 2> p1, std::array<float, 2> p2);
	bool isColliding();

	std::shared_ptr<sf::RenderWindow> m_window;
	std::vector <std::shared_ptr<std::thread>> m_threadPool;
	sf::VertexArray m_vertices;
	
	float m_quadLen;
	int m_selectedQuad;
	std::vector<sf::Vector2f> m_quadOrigin;
};