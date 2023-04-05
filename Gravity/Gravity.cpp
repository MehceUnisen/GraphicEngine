#include "Gravity.h"

Gravity::Gravity(const sf::RenderWindow& window, uint16_t amount) :
	m_window(window),
	ObjectHandler(amount)
{
	
}

void Gravity::applyGravity(const ObjectHandler& objectHandler) {
	getMousePosition();
	for (uint64_t i = 0; i < const_cast<ObjectHandler&>(objectHandler).getObjectCount(); i++)
	{
	}
}

sf::Vector2f Gravity::getMousePosition() {
	sf::Vector2i mouse = sf::Mouse::getPosition(m_window);
	return m_window.mapPixelToCoords(mouse);
}
