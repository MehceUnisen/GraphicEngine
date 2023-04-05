#include "ObjectHandler.h"

class Gravity : public ObjectHandler {

public:
	Gravity(const sf::RenderWindow& window, uint16_t amount);

	void applyGravity(const ObjectHandler& objectHandler);
	sf::Vector2f getMousePosition();

private:
	const float m_g = 9.807f;
	const sf::RenderWindow& m_window;
};

