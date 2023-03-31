#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <functional>

class Gradient {
public:
	Gradient(uint8_t step);

private:

	void update();
	void changeColor(std::size_t index);
	const uint8_t m_shrinkFactor = 4;
	const uint16_t m_windowDimension = 1000;
	
	std::shared_ptr<sf::RenderWindow> m_window;
	sf::VertexArray m_gradientMap;
	sf::Vector2f m_cursorPos;
	int m_column{ 0 };
	int m_pixel{ 0 };
	float m_vertexDimension;
	uint32_t m_vertexCount;
};