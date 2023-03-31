#include "Particle.h"
#include <vector>
#include <thread>
#include <random>

class ParticleGenerator {
public:
	ParticleGenerator(uint32_t count);
	
private:
	
	void fadePartical(uint32_t index, const Particle& particle, sf::Time timeElapsed);
	void update(sf::Time timeElapsed);
	void resetParticle(uint32_t index, const Particle& particle);
	void getCursor(const sf::RenderWindow& window);

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifeTime;
	sf::Vector2f m_cursor;

	std::shared_ptr<sf::RenderWindow> m_window;
};