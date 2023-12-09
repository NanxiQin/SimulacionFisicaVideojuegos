#pragma once
#include "ParticleGenerator.h"
#include <random>
class SimpleParticleGenerator:public ParticleGenerator
{
public:
	SimpleParticleGenerator(GeneratorEffectProperties prop);
	SimpleParticleGenerator(Particle* modelParticle, Vector3 originOffset, DistributionProp distribution, double minLifeT, double maxLifeT);
	list<Particle*>generateParticles() override;

	Vector3 generateNewDistribution()override;
private:
	uniform_real_distribution<double> uniform_x;
	uniform_real_distribution<double> uniform_y;
	uniform_real_distribution<double> uniform_z;
};
