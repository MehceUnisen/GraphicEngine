#include "PixelGenerator.h"

PixelGenerator::PixelGenerator(uint8_t p_density = 50) {
	m_density = p_density;
	srand(time(NULL));

	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 800), "PixelGenerator");

	for (int i = 0; i < m_density * SCALE_FACTOR; i++)
	{
		m_pixelAtlas.push_back(sf::RectangleShape(sf::Vector2f(5.0f, 5.0f)));
		m_pixelAtlas.at(i).setPosition(rand() % 795, rand() % 795);
		m_pixelAtlas.at(i).setFillColor(m_pixelColor);
	}

	while (m_window->isOpen()) {
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
		}
		m_window->clear();
		for (sf::RectangleShape rect : m_pixelAtlas)
		{
			m_window->draw(rect);
		}
		m_window->display();
	}
}

PixelGenerator::~PixelGenerator() {
	if (m_window != nullptr)
	{
		m_window->close();
	}
}
