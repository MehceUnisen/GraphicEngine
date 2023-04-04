#include "Particle.h"
#include <vector>
#include <map>

//template <typename T>

class ParticleHandler {
public:
	ParticleHandler();
	void appendParticle(const Particle& particle);
	Particle at(uint64_t index);

private:
	std::vector<Particle> m_particles;
};