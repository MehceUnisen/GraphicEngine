#include "ParticleHandler.h"

ParticleHandler::ParticleHandler() {

}

void ParticleHandler::appendParticle(const Particle& particle) {
	m_particles.push_back(particle);
}

Particle ParticleHandler::at(uint64_t index) {
	return m_particles.at(index);
}