#include "Gradient.h"

Gradient::Gradient(uint8_t step) : 
	m_cursorPos(0.0f, 0.0f),
	m_gradientMap(sf::Quads, static_cast<std::size_t>(ceil(step / 80.0f)) * pow(m_windowDimension / m_shrinkFactor, 2) * 8),
	m_vertexCount (static_cast<uint32_t>(sqrt(m_gradientMap.getVertexCount()) / 4))
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_windowDimension, m_windowDimension), "Gradient");
	m_vertexDimension = static_cast<float>(m_windowDimension) / static_cast<float>(m_vertexCount);

	sf::Thread worker(std::bind(&Gradient::update, this));
	while (m_window->isOpen()) { 
		sf::Event event;

		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
				worker.terminate();
			}
			
		}
		m_window->setActive(false);
		worker.launch();

	}
}

void Gradient::update() {
	m_window->setActive(true);
	for (size_t i = 0; i < m_vertexCount; i++)
	{
		for (size_t j = 0; j < m_vertexCount; j++)
		{
			m_gradientMap[m_pixel].position = sf::Vector2f(m_vertexDimension * m_column, m_vertexDimension * i);
			m_gradientMap[m_pixel + 1].position = sf::Vector2f(m_vertexDimension * m_column + m_vertexDimension, m_vertexDimension * i);
			m_gradientMap[m_pixel + 2].position = sf::Vector2f(m_vertexDimension * m_column + m_vertexDimension, m_vertexDimension * i + m_vertexDimension);
			m_gradientMap[m_pixel + 3].position = sf::Vector2f(m_vertexDimension * m_column, m_vertexDimension * i + m_vertexDimension);

			m_gradientMap[m_pixel].color = sf::Color::Red;
			m_gradientMap[m_pixel + 1].color = sf::Color::Green;
			m_gradientMap[m_pixel + 2].color = sf::Color::Blue;
			m_gradientMap[m_pixel + 3].color = sf::Color::Black;
			m_pixel += 4;
			m_column++;
			
		}
		m_window->draw(m_gradientMap);
		m_window->display();
		m_column = 0;
	}
	m_window->setActive(false);
	m_pixel = 0;
}

void Gradient::getCursorPos() {
	sf::Vector2i cursorPos = sf::Mouse::getPosition(*m_window);
	m_cursorPos = m_window->mapPixelToCoords(cursorPos);
}

bool Gradient::isLeftMouseClicked(sf::Event& event) {
	
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		return true;
	}

	return false;
}