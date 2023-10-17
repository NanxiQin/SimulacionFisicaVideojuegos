#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem(Scene* scene, const Vector3& g) :System(scene), gravity(g)
{
	/*createGenerator<SimpleParticleGenerator>(Default,{-50,0,0});*/
	//createGenerator<GaussianParticleGenerator>(Default,{50,0,0},Blue);
	//createGenerator<SimpleParticleGenerator>(FogEffect);
	//createGenerator<SimpleParticleGenerator>(HoseEffect);
	//createGenerator<GaussianParticleGenerator>(MilkyWayEffect);
	generateFirework();
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
	delete firework_generator;
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
		if (isOutOfBounds(particle->getPos())) particle->setAlive(false);
	}

	//for (auto i : particleNum) cout << i << " ";
	//cout << endl;
}

void ParticleSystem::refresh()
{
	auto it = particles.begin();
	while (it != particles.end()) {
		Particle* p = *it;
		if (!p->isAlive()) {
			onParticleDeath(p);
			it = particles.erase(it);
			p->die();
		}
		else ++it;

	}
	// TODO

	/*particles.erase(
		std::remove_if(particles.begin(), particles.end(),
			[](Particle* p, ParticleSystem* t) {
				if (p->isAlive()) {
					return false;
				}
				else {
					p->die();
					return true;
				}
			}),
		particles.end());*/
}

void ParticleSystem::keyPress(unsigned char key, const PxTransform& camera)
{
	for (auto g : particleGenerators) g->keyPress(key);
}

void ParticleSystem::generateFirework()
{
	firework_generator = new SimpleParticleGenerator(generatorEffect[FireworkEffect]);
	Firework* f = new Firework(particleProperties[FIREWORK], firework_generator);
	addParticles({ f });
}

void ParticleSystem::addParticles(list<Particle*> particlesList)
{
	for (auto p : particlesList) {
		particles.push_back(p);
		//++particleNum[p->getType()];
	}
}

void ParticleSystem::onParticleDeath(Particle* p) {
	//--particleNum[p->getType()];
	if (p->getType() == FIREWORK) {
		Firework* f = static_cast<Firework*>(p);
		auto l=f->explode();
		for (auto newP : l) {
			particles.push_back(newP);
			Firework* aux= static_cast<Firework*>(newP);
			aux->addGenerator(firework_generator);
			cout << f->getNGen() << endl;
			//aux->setNGen(f->getNGen()+1);
			//++particleNum[newP->getType()];

		}
	}
	//addParticles(static_cast<Firework*>(p)->explode());

}