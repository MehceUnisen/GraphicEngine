#include <SFML/Graphics.hpp>
#include <vector>
#include <map>


class ObjectHandler : public sf::Drawable {
private:

struct Object {
		sf::Vector2f velocity;
		float time;

		Object(sf::Vector2f vel, sf::Time t) {
			velocity = vel;
			time = t.asSeconds();
		}
	};

public:
	ObjectHandler(uint16_t amount);
	
	void addObject(sf::Vector2f position);
	void resetObject(uint64_t index);

	uint16_t getObjectCount();
	
	virtual void update(float gravity, sf::Time t);

	sf::Time totalTime;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_vertices, states);
	}
	
	void fixedUpdate(uint16_t index);
	
	uint16_t m_objectCount;
	std::vector<Object> m_objects;
	sf::VertexArray m_vertices;
};