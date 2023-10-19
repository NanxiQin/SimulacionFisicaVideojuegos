#pragma once
#include "ParticleGenerator.h"
#include <random>
class SimpleParticleGenerator:public ParticleGenerator
{
public:
	SimpleParticleGenerator(GeneratorEffectProperties prop);
	list<Particle*>generateParticles() override;


private:
	uniform_real_distribution<double> uniform_x;
	uniform_real_distribution<double> uniform_y;
	uniform_real_distribution<double> uniform_z;
};

