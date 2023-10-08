#pragma once
#include "Particle.h"
#include <list>
#include "ParticleGenerator.h"
class Firework :public Particle
{
public:
	// The firework generates more fireworks when exploding --> they should be gathered by the System
	list<Particle*> explode();
	void addGenerator(ParticleGenerator* p);
	virtual Particle* clone() const;

protected:
	// Type
	unsigned _type;
	list<shared_ptr<ParticleGenerator> > _gens;
};


