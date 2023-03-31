#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <functional>
class PencilSimulator {
public:
	PencilSimulator();
	
private:
	
	void update();
	void clear();
	
	std::shared_ptr<sf::RenderWindow> m_window;
	sf::Vector2f m_cursor;
	sf::VertexArray m_vertices;
	bool m_lockClick{false};
};
