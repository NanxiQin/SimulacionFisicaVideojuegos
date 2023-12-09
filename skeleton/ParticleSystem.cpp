#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(Scene* scene, const Vector3& g) :
	System(scene), shooter(new ShooterManager(this)), gravity(g), forceRegistry(new ParticleForceRegistry()), gravityForce(new GravityForceGenerator(g)), floatingForce(new GravityForceGenerator(FLOAT_FORCE)), hasGravity(true)
{
	forceGenerators.push_back(gravityForce);
	forceGenerators.push_back(floatingForce);
}

ParticleSystem::~ParticleSystem()
{
	cleanSystem();
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

void ParticleSystem::cleanSystem()
{
	deleteAllParticleGenerators();
	for (auto g : firework_generators) delete g;
	firework_generators.clear();

	for (auto fg : forceGenerators) {
		deregisterForceGenerator(fg);
		delete fg;
	};
	forceGenerators.clear();

	auto it = particles.begin();
	while (it != particles.end()) {
		auto particle = *it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		delete particle;

	}
	particles.clear();

	for (auto& a : particleNum) a = 0;

	delete shooter;
	delete forceRegistry;
}

void ParticleSystem::resetSystem()
{
	cleanSystem();

	forceRegistry = new ParticleForceRegistry();
	shooter=new ShooterManager(this);
	
	gravityForce = new GravityForceGenerator(gravity);
	floatingForce = new GravityForceGenerator(FLOAT_FORCE);
	forceGenerators.push_back(gravityForce);
	forceGenerators.push_back(floatingForce);
	createFireworkGenerators();
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
	f->setVel(f->getVel() * GetCamera()->getDir()) ;
	f->setPos(GetCamera()->getEye());
	addParticles({ f });
}


void ParticleSystem::createFireworkGenerators()
{
	initFirework<SimpleParticleGenerator>(1, 10);
	initFirework<GaussianParticleGenerator>(0.8, 5); //+gen gau
	initFirework<GaussianParticleGenerator>(0.5, 5); //random -prob
}

void ParticleSystem::addGravity(Particle* particle)
{
	if (particle != nullptr) forceRegistry->addParticleRegistry(gravityForce, particle);
}

void ParticleSystem::addFloating(Particle* particle)
{
	if (particle != nullptr)forceRegistry->addParticleRegistry(floatingForce, particle);
}

void ParticleSystem::addForcetoAllParticlegenerators(list<ForceGenerator*> fg)
{
	for (auto g : particleGenerators)
		g->addForceGenerators(fg);
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
			aux->setNGen(f->getNGen() + 1);
			addParticles({ aux });
		}
	}

}

void ParticleSystem::addForcetoAllParticles(list <ForceGenerator*> fg)
{
	for (auto p : particles)
		for (auto f : fg)
			forceRegistry->addParticleRegistry(f, p);
}

void ParticleSystem::deleteAllParticleGenerators()
{
	for (auto g : particleGenerators) {
		forceRegistry->deleteParticleGenRegistry(g);
		delete g;
	}
	particleGenerators.clear();
}
void ParticleSystem::deleteParticleGenerator(ParticleGenerator* gen)
{
	forceRegistry->deleteParticleGenRegistry(gen);
	particleGenerators.remove(gen);
	delete gen;
}
void ParticleSystem::deregisterForceGenerator(ForceGenerator* fg)
{
	forceRegistry->deleteForceRegistry(fg);
}
void ParticleSystem::deregisterForceGeneratorFromGen(ForceGenerator* fg, ParticleGenerator* gen)
{
	forceRegistry->deleteForceRegistryFromGen(fg, gen);
}

void ParticleSystem::deleteForceGenerator(ForceGenerator* fg)
{
	if (fg->getType() == GravityForce) return;
	deregisterForceGenerator(fg);
	forceGenerators.remove(fg);
	delete fg;
}


void ParticleSystem::debugNumParticle()
{
	for (auto i : particleNum) cout << i << " ";
	cout << endl;
}
