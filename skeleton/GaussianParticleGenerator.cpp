#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(GeneratorEffectProperties prop) :
	ParticleGenerator(prop.model, prop.originOffset, prop.minLifeTime, prop.maxLifeTime),
	normal_x(normal_distribution<double>{ prop.distribution.x.first, prop.distribution.x.second }),
	normal_y(normal_distribution<double>{ prop.distribution.y.first, prop.distribution.y.second }),
	normal_z(normal_distribution<double>{ prop.distribution.z.first, prop.distribution.z.second })
{}
GaussianParticleGenerator::GaussianParticleGenerator(Particle * modelParticle, Vector3 originOffset, DistributionProp distribution,double minLifeT, double maxLifeT):
	ParticleGenerator(modelParticle,originOffset, minLifeT, maxLifeT),
	normal_x(normal_distribution<double>{ distribution.x.first, distribution.x.second }),
	normal_y(normal_distribution<double>{ distribution.y.first, distribution.y.second }),
	normal_z(normal_distribution<double>{ distribution.z.first, distribution.z.second })
{}
list<Particle*> GaussianParticleGenerator::generateParticles()
{
	return generalParticleGeneration();
}

Vector3 GaussianParticleGenerator::generateNewDistribution() {
	return Vector3(normal_x(mt), normal_y(mt), normal_z(mt));
};