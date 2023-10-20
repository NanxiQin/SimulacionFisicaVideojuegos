#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(Scene* scene, const Vector3& g) :System(scene), gravity(g)
{
	initFirework();
}

ParticleSystem::~ParticleSystem()
{
	auto it = particles.begin();
	while (it != particles.end()) {
		auto particle = *it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		delete particle;
	}

	for (auto g : particleGenerators) delete g;
	delete firework_generator;
}

void ParticleSystem::update(double t)
{
	refresh();
	//generar nuevas partículasS
	for (auto g : particleGenerators)
		addParticles(g->generateParticles());

	auto it = particles.begin();
	while (it != particles.end()) {
		auto particle = *it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		particle->update(t);
		//chequear deathzone
		if (isOutOfBounds(particle->getPos())) particle->setAlive(false);
	}

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
}

void ParticleSystem::keyPress(unsigned char key, const PxTransform& camera)
{
	switch (key)
	{
	case shoot_Firework1:
		generateFirework(true);
		break;
	case shoot_Firework2:
		generateFirework(false);
		break;
	case add_UniformGen:
		createGenerator<SimpleParticleGenerator>(true, Default, { -50,0,0 }, Pink);
		break;
	case add_GaussianGen:
		createGenerator<GaussianParticleGenerator>(true, Default, { -50,0,0 }, Green);
		break;
	case add_HoseEffect:
		createGenerator<GaussianParticleGenerator>(true, HoseEffect);
		break;
	case add_FogEffect:
		createGenerator<GaussianParticleGenerator>(true, FogEffect);
		break;
	case add_RainEffect:
		createGenerator<SimpleParticleGenerator>(true, RainEffect);
		break;
	case add_MilkyEffect:
		createGenerator<SimpleParticleGenerator>(true, MilkyWayEffect);
		break;
	case 'f':
		if (!particleGenerators.empty()) particleGenerators.pop_back();
		break;


	default:
		break;
	}

}

void ParticleSystem::initFirework()
{
	firework_generator = createGenerator<GaussianParticleGenerator>(false, FireworkEffect);
	firework_generator->setNParticles(5);
}

void ParticleSystem::generateFirework(bool randomColor)
{
	Firework* f = new Firework(particleProperties[FIREWORK], firework_generator, 0, true, randomColor);
	f->getVel() = f->getVel() * GetCamera()->getDir();
	f->getPos() = GetCamera()->getEye();
	addParticles({ f });
}


void ParticleSystem::addParticles(list<Particle*> particlesList)
{
	for (auto p : particlesList) {
		particles.push_back(p);
		++particleNum[p->getType()];
	}
}

void ParticleSystem::onParticleDeath(Particle* p) {
	--particleNum[p->getType()];
	if (p->getType() == FIREWORK) {
		Firework* f = static_cast<Firework*>(p);
		auto l = f->explode();
		for (Particle* newP : l) {
			Firework* aux = static_cast<Firework*>(newP);
			aux->addGenerator(firework_generator);
			aux->setNGen(f->getNGen() + 1);
			addParticles({ aux });
		}
	}


}

void ParticleSystem::debugNumParticle()
{
	for (auto i : particleNum) cout << i << " ";
	cout << endl;
}
