#include "SimpleParticleGenerator.h"
#include <random> 
SimpleParticleGenerator::SimpleParticleGenerator(ParticleProperties modelParticle, Vector3 originOffset = { 0,0,0 }, double min, double max) :
	ParticleGenerator(modelParticle, originOffset), uniform_dis(uniform_real_distribution<double>{ min, max }) {}

list<Particle*> SimpleParticleGenerator::generateParticles()
{
	list<Particle*> list;
	if (checkGenerationProb()) //generar según prob
		//int color = rand() % COLOR_SIZE;
		for (int i = 0; i < _n_particles; ++i) {
			Vector3 v = Vector3(uniform_dis(mt), uniform_dis(mt), uniform_dis(mt)) * _mean_velocity;
			list.push_back(new Particle({ PxTransform(_origin),v,Vector3(0,GRAVITY,0),DEFAULT_DAMPING,mass,colorRGB[Orange],UNIFORM_LIFETIME }));
		}
	return list;
}
