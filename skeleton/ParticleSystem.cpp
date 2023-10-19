#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem(Scene* scene, const Vector3& g) :System(scene), gravity(g)
{
	/*createGenerator<SimpleParticleGenerator>(true,Default,{-50,0,0});*/
	//createGenerator<GaussianParticleGenerator>(true,Default,{50,0,0},Blue);
	//createGenerator<SimpleParticleGenerator>(true,FogEffect);
	//createGenerator<SimpleParticleGenerator>(true,HoseEffect);
	//createGenerator<GaussianParticleGenerator>(true,MilkyWayEffect);
	initFirework();
}

ParticleSystem::~ParticleSystem()
{
	// TODO
	auto it = particles.begin();
	while (it != particles.end()) {
		auto particle = *it; //hacerlo con un iterador auxiliar, por si se invalida durante el bucle (por borrarlo)
		++it;
		delete particle;
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
	//DUDA: A BORRAR
	//for (auto g : particleGenerators) g->keyPress(key);
	switch (key)
	{
	case shoot_Firework:
		generateFirework();
		break;
	default:
		break;
	}
		

}

void ParticleSystem::generateFirework()
{
	Firework* f = new Firework(particleProperties[FIREWORK], firework_generator,0);
	f->getVel() = f->getVel()* GetCamera()->getDir();
	f->getPos() = GetCamera()->getEye();
	addParticles({ f });
}

void ParticleSystem::initFirework()
{
	firework_generator = createGenerator<SimpleParticleGenerator>(false, FireworkEffect);
	firework_generator->setNParticles(5);
}

void ParticleSystem::addParticles(list<Particle*> particlesList)
{
	for (auto p : particlesList) {
		particles.push_back(p);
		++particleNum[p->getType()];
	}
	for (auto i : particleNum) cout << i << " ";
	cout << endl;
}

void ParticleSystem::onParticleDeath(Particle* p) {
	--particleNum[p->getType()];
	if (p->getType() == FIREWORK) {
		Firework* f = static_cast<Firework*>(p);
		auto l=f->explode();
		for (Particle* newP : l) {
			Firework* aux= static_cast<Firework*>(newP);
			aux->addGenerator(firework_generator);
			aux->setNGen(f->getNGen()+1);
			cout << aux->getNGen() << endl;
			particles.push_back(aux);
			++particleNum[newP->getType()];
			
		}
	}
	for (auto i : particleNum) cout << i << " ";
	cout << endl;
	//addParticles(static_cast<Firework*>(p)->explode());

}