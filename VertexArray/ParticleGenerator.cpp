#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(uint32_t count) :
	m_particles(count),
	m_vertices(sf::Points, count),
	m_lifeTime(sf::seconds(3.f)),
	m_cursor(0.f, 0.f)
{
	srand(time(NULL));
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 768), "Particle Generator");
	
	sf::Clock clock;

	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();
		}
		getCursor(*m_window);

		sf::Time elapsed = clock.restart();
		update(elapsed);

		m_window->clear();
		m_window->draw(m_vertices);
		m_window->display();
	}
}

void ParticleGenerator::fadePartical(uint32_t index, const Particle& particle, sf::Time timeElapsed) {
	m_vertices[index].position += particle.velocity * timeElapsed.asSeconds();
	m_vertices[index].color.a = static_cast<uint8_t>(particle.lifeTime.asSeconds() / m_lifeTime.asSeconds() * 255);
}

void ParticleGenerator::resetParticle(uint32_t index, const Particle& particle) {
	float angle = static_cast<float>(std::rand() % 360) * 3.14f / 180;
	float speed = static_cast<float>(std::rand() % 50) + 50.0f;
	
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifeTime = sf::milliseconds((std::rand() % 2000) + 1000);

	m_vertices[index].position = m_cursor;

}

void ParticleGenerator::update(sf::Time timeElapsed) {
	for (uint32_t i = 0; i < m_particles.size(); ++i)
	{
		Particle& particle = m_particles.at(i);
		particle.lifeTime -= timeElapsed;
	
		if (particle.lifeTime <= sf::Time::Zero) 
			resetParticle(i, particle);
		else
			fadePartical(i, particle, timeElapsed);

		float rColor = m_vertices[i].position.x / 1024 * 255;
		float bColor = m_vertices[i].position.y / 768 * 255;
		
		m_vertices[i].color = sf::Color(rColor, 0, bColor);
	}
}


void ParticleGenerator::getCursor(const sf::RenderWindow& window) {
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	m_cursor = window.mapPixelToCoords(mouse);
}
