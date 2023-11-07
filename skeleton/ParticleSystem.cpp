#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(Scene* scene, const Vector3& g) :System(scene), shooter(new ShooterManager(this)), gravity(g), forceRegistry(new ParticleForceRegistry()), gravityForce(new GravityForceGenerator(g)), floatingForce(new GravityForceGenerator(FLOAT_FORCE))
{
	createFireworkGenerators();

	forceGenerators.push_back(gravityForce);
	forceGenerators.push_back(floatingForce);


	auto gen = createGenerator<SimpleParticleGenerator>(true, NeutralEffect, { 0,0,0 }, Blue);
	auto e = new WindForceGenerator(0.3, { 10,5,0 });
	/*auto gen = createGenerator<SimpleParticleGenerator>(true, NeutralEffect, { 0,0,0 }, Blue);
	auto e = new ExplosionForceGenerator({ 10,0,0 }, 1000, 1000, 5);*/
	forceGenerators.push_back(e);

	gen->addForceGenerators({ e, gravityForce });
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
	particleGenerators.clear();
	for (auto g : firework_generators) delete g;
	firework_generators.clear();
	for (auto g : forceGenerators)delete g;
	forceGenerators.clear();

	delete shooter;
	delete forceRegistry;
}

void ParticleSystem::update(double t)
{
	refresh();

	shooter->update(t);
	forceRegistry->updateForces(t);
	for (auto g : forceGenerators) g->updateTime(t);
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
			forceRegistry->deleteParticleRegistry(p);
			it = particles.erase(it);
			p->die();
		}
		else ++it;

	}

	auto f_it = forceGenerators.begin();
	while (f_it != forceGenerators.end()) {
		ForceGenerator* f = *f_it;
		if (!f->isAlive()) {
			forceRegistry->deleteForceRegistry(f);
			delete* f_it;
			f_it = forceGenerators.erase(f_it);
		}
		else ++f_it;

	}
}

void ParticleSystem::keyPress(unsigned char key, const PxTransform& camera)
{
	switch (key)
	{
	case shoot_Firework1:
		generateFirework(false, 3, 0);
		break;
	case shoot_Firework2:
		generateFirework(false, 5, 1);
		break;
	case shoot_Firework3:
		generateFirework(true, 5, 2);
		break;
	case add_UniformGen:
		createGenerator<SimpleParticleGenerator>(true, DefaultEffect, { -50,0,0 }, Pink)->addForceGenerators({ gravityForce });
		break;
	case add_GaussianGen:
		createGenerator<GaussianParticleGenerator>(true, DefaultEffect, { -50,0,0 }, Green)->addForceGenerators({ gravityForce });
		break;
	case add_HoseEffect:
		createGenerator<SimpleParticleGenerator>(true, HoseEffect)->addForceGenerators({ gravityForce });
		break;
	case add_FogEffect:
		createGenerator<GaussianParticleGenerator>(true, FogEffect);
		break;
	case add_RainEffect:
		createGenerator<SimpleParticleGenerator>(true, RainEffect)->addForceGenerators({ gravityForce });
		break;
	case add_MilkyEffect:
		createGenerator<SimpleParticleGenerator>(true, MilkyWayEffect);
		break;
	case add_Uniwind:
		(particleGenerators.back())->addForceGenerators({ new WindForceGenerator(0.3, { 10,5,0 }) });
		break;
	case add_Windwhirl:
		(particleGenerators.back())->addForceGenerators({ new WhirlwindsForceGenerator(1, 0.8) });
		break;
	case add_Explosion:
		(particleGenerators.back())->addForceGenerators({ new ExplosionForceGenerator({ 10,0,0}, 1000, 1000, 5) });
		break;
	case 'f':
		if (!particleGenerators.empty()) {
			deleteGenerator(particleGenerators.back());
			particleGenerators.pop_back();
		}
		break;
	case 'g':
		deregisterForceGenerator(gravityForce);
		break;

	default:
		shooter->keyPress(key);
		break;
	}

}

template <typename T>
void ParticleSystem::initFirework(double prob, int nParticle)
{
	auto g = createGenerator<T>(false, FireworkEffect);
	g->setGenProb(prob);
	g->setNParticles(nParticle);
	g->addForceGenerators({ gravityForce });
	firework_generators.push_back(g);
}

void ParticleSystem::generateFirework(bool randomColor, int maxGen, int gen)
{
	Firework* f = new Firework(particleProperties[FIREWORK], firework_generators[gen], 0, maxGen, true, randomColor);
	f->getVel() = f->getVel() * GetCamera()->getDir();
	f->getPos() = GetCamera()->getEye();
	addParticles({ f });
}


void ParticleSystem::createFireworkGenerators()
{
	initFirework<SimpleParticleGenerator>(1, 10);
	initFirework<GaussianParticleGenerator>(0.8, 5); //+gen gau
	initFirework<GaussianParticleGenerator>(0.5, 5); //random -prob
}

void ParticleSystem::createForceGenerators()
{
}

void ParticleSystem::deregisterForceGenerator(ForceGenerator* fg)
{
	forceRegistry->deleteForceRegistry(fg);
}

void ParticleSystem::addParticles(list<Particle*> particlesList)
{
	for (auto p : particlesList) {
		particles.push_back(p);
		++particleNum[p->getType()];
	}
}

void ParticleSystem::addGravity(Particle* particle)
{
	if (particle != nullptr) forceRegistry->addParticleRegistry(gravityForce, particle);
}

void ParticleSystem::addFloating(Particle* particle)
{
	if (particle != nullptr)forceRegistry->addParticleRegistry(floatingForce, particle);
}

void ParticleSystem::onParticleDeath(Particle* p) {
	--particleNum[p->getType()];
	if (p->getType() == FIREWORK) {
		Firework* f = static_cast<Firework*>(p);
		auto l = f->explode();
		for (Particle* newP : l) {
			Firework* aux = static_cast<Firework*>(newP);
			aux->setNGen(f->getNGen() + 1);
			addParticles({ aux });
		}
	}

}

void ParticleSystem::deleteGenerator(ParticleGenerator* gen)
{
	forceRegistry->deleteParticleGenRegistry(gen);
	delete gen;
}

void ParticleSystem::debugNumParticle()
{
	for (auto i : particleNum) cout << i << " ";
	cout << endl;
}
