#include "Particle.h"

Particle::Particle(sf::Vector2f position) :
	sf::Vertex(position),
	m_velocity(0.0f)
{
}

float Particle::getVelocity() {
	return m_velocity;
}

float Particle::setVelocity(float velocity) {
	m_velocity = velocity;
}
