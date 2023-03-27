#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <SFML/Graphics.hpp>

#define IN_PROCESS_COLOR sf::Color::Green
#define IDLE_COLOR sf::Color::White
#define COLUMN_WIDTH 5.0f
#define MAX_HEIGHT 800

class BubbleSort {

public:
	BubbleSort(int p_amount);
	~BubbleSort();

private:

	std::shared_ptr<sf::RenderWindow> m_window;
	std::vector<sf::RectangleShape> m_atlas;

	int m_amount;
	bool m_sorted;

	void drawArray();
	void sort();
};