#include "SimpleParticleGenerator.h"
#include <random> 
#include <iostream>

SimpleParticleGenerator::SimpleParticleGenerator(GeneratorEffectProperties prop) :
	ParticleGenerator(prop.model, prop.originOffset, prop.minLifeTime, prop.maxLifeTime),
	uniform_x(uniform_real_distribution<double>{ prop.distribution.x.first, prop.distribution.x.second }),
	uniform_y(uniform_real_distribution<double>{ prop.distribution.y.first, prop.distribution.y.second }),
	uniform_z(uniform_real_distribution<double>{ prop.distribution.z.first, prop.distribution.z.second }) {}

SimpleParticleGenerator::SimpleParticleGenerator(Particle* modelParticle, Vector3 originOffset, DistributionProp distribution, double minLifeT, double maxLifeT) :
	ParticleGenerator(modelParticle, originOffset, minLifeT, maxLifeT),
	uniform_x(uniform_real_distribution<double>{ distribution.x.first, distribution.x.second }),
	uniform_y(uniform_real_distribution<double>{ distribution.y.first, distribution.y.second }),
	uniform_z(uniform_real_distribution<double>{ distribution.z.first, distribution.z.second })
{}
list<Particle*> SimpleParticleGenerator::generateParticles()
{
	return generalParticleGeneration();
}

Vector3 SimpleParticleGenerator::generateNewDistribution() {
	return Vector3(uniform_x(mt), uniform_y(mt), uniform_z(mt));
};