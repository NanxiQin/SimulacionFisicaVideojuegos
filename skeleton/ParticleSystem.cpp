#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Scene* scene, const Vector3& g) :System(scene), gravity(g)
{
	particleGenerators.push_back(new SimpleParticleGenerator(UNIFORM_ORIGIN, UNIFORM_VELOCITY, 1));
	particleGenerators.push_back(new GaussianParticleGenerator(NORMAL_ORIGIN, NORMAL_VELOCITY));
}

ParticleSystem::~ParticleSystem()
{
	// TODO
	auto it = particles.begin();
	while (it != particles.end()) {
		auto particle = *it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		particle->die();
	}
	
	for (auto g : particleGenerators)
		delete g;

}

void ParticleSystem::update(double t)
{
	refresh();
	//generar nuevas partículasS
	for (auto g : particleGenerators)
		addParticles(g->generateParticles());


	// TODO
	auto it = particles.begin();
	while (it != particles.end()) {
		auto particle = *it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		particle->update(t);
		//chequear deathzone
		if (isOutOfBounds(particle->getPos())) particle->setAlive(false) ;
	}
}

void ParticleSystem::refresh()
{
	// TODO
	particles.erase(
		std::remove_if(particles.begin(), particles.end(),
			[](Particle* p) {
				if (p->isAlive()) {
					return false;
				}
				else {
					p->die();
					return true;
				}
			}),
		particles.end());
}

void ParticleSystem::keyPress(unsigned char key, const PxTransform& camera)
{
	for (auto g : particleGenerators) g->keyPress(key);
}

void ParticleSystem::addParticles(list<Particle*> particlesList)
{
	for (auto p : particlesList) {
		particles.push_back(p);
	}
}

