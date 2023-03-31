#include "PencilSimulator.h"

PencilSimulator::PencilSimulator() {
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 768), "Pencil Simulator");

	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
		}
		if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased || m_lockClick)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				clear();
			}
			else if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
			{
				m_lockClick = false;
			}
			else if (event.mouseButton.button == sf::Mouse::Left || m_lockClick)
			{
				sf::Thread worker(std::bind(&PencilSimulator::update, this));
				worker.launch();
				m_lockClick = true;
			}
						
		}
		m_window->clear();
		m_window->draw(m_vertices);
		m_window->display();
	}
}

void PencilSimulator::update() {
		sf::Vector2i cursorPos = sf::Mouse::getPosition(*m_window);
		m_cursor = m_window->mapPixelToCoords(cursorPos);
		m_vertices.append(sf::Vertex(sf::Vector2f(m_cursor.x, m_cursor.y), sf::Color::White));
}

void PencilSimulator::clear() {
	m_vertices.clear();
}