#include <SFML/Graphics.hpp>
#include <thread>

class Collision {

public:
	Collision();

private:
	
	void renderVertices();
	void renderQuad(sf::Vector2f coord, float quadLen, std::size_t index);
	void takeInput();
	void move(std::size_t index, sf::Vector2f coord);

	sf::Vector2f calculateDistance();

	std::shared_ptr<sf::RenderWindow> m_window;
	std::vector <std::shared_ptr<std::thread>> m_threadPool;
	sf::VertexArray m_vertices;
	
	float m_quadLen;
	int m_selectedQuad;
	std::vector<sf::Vector2f> m_quadOrigin;
};