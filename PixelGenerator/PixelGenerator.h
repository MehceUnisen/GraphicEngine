#pragma once

#define SCALE_FACTOR 100

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <future>
#include <iostream>
#include <vector>
#include <cstdint>

class PixelGenerator {
public:
	PixelGenerator(uint8_t p_density);
	~PixelGenerator();


private:

	std::vector<sf::RectangleShape> m_pixelAtlas;
	uint8_t m_density = 50;
	sf::Color m_pixelColor = sf::Color::Red;
	std::shared_ptr<sf::RenderWindow> m_window;
};

