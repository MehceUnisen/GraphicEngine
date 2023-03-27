#include "SortingAlgorithm.h"

BubbleSort::BubbleSort(int p_amount) {
	m_amount = p_amount;
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(MAX_HEIGHT, MAX_HEIGHT), "Sorter");
	srand(time(NULL));
	for (int i = 0; i < m_amount; i++)
	{
		int height = rand() % MAX_HEIGHT;
		m_atlas.push_back(sf::RectangleShape(sf::Vector2f(
			COLUMN_WIDTH, height)));
		m_atlas.at(i).setPosition((i + 1) * COLUMN_WIDTH, MAX_HEIGHT - height);
		m_atlas.at(i).setFillColor(IDLE_COLOR);
	}
	m_window->clear();
	drawArray();

	while (m_window->isOpen()) {
		sf::Event event;
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
		}
		if (!m_sorted) {
			sort();
		}
	}
}

BubbleSort::~BubbleSort() {

}

void BubbleSort::drawArray() {
	m_window->clear();
	for (int i = 0; i < m_amount; i++)
	{
		m_window->draw(m_atlas.at(i));
	}
	m_window->display();
}

void BubbleSort::sort() {
	for (int i = 0; i < m_amount - 1; i++)
	{
		for (int j = 0; j < m_amount - 1; j++)
		{
			if (m_atlas.at(j).getSize().y > m_atlas.at(j + 1).getSize().y)
			{
				m_atlas.at(j).setFillColor(IN_PROCESS_COLOR);
				drawArray();
				std::swap(m_atlas.at(j), m_atlas.at(j + 1));

				m_atlas.at(j).move(sf::Vector2f(-COLUMN_WIDTH, 0.0f));
				m_atlas.at(j + 1).move(sf::Vector2f(COLUMN_WIDTH, 0.0f));
			}

			drawArray();
		}
	}
	m_sorted = true;
}

