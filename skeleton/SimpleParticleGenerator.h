#pragma once
#include "ParticleGenerator.h"
#include <random>
class SimpleParticleGenerator:public ParticleGenerator
{
public:
	SimpleParticleGenerator(ParticleProperties modelParticle, Vector3 originOffset = { 0,0,0 } , double min= UNIFORM_MIN, double max= UNIFORM_MAX);
	list<Particle*>generateParticles() override;
private:
	uniform_real_distribution<double> uniform_dis;
	double mass;
};

