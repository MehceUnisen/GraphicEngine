#include <SFML/Graphics.hpp>

//template <typename... T>
//class Particle;
//
//template<typename T>
class Particle : public sf::Vertex, public sf::Drawable {
public:
	Particle(sf::Vector2f position);

	float getVelocity();
	float setVelocity(float velocity);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const {
		target.draw(*this, state);
	};
	float m_velocity;
	
};
