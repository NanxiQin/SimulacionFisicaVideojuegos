#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 pos, Vector3 vel):ParticleGenerator(), pos(pos),vel(vel)
{
	mt = mt19937{ random_device()() };
	_mean_velocity = vel;
	_origin = pos;
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> list;

	if (checkGenerationProb()) //generar según prob
		for (int i = 0; i < _n_particles; ++i) {
			Vector3 v = Vector3(normal_dis(mt), normal_dis(mt), normal_dis(mt)) * _mean_velocity;
			list.push_back(new Particle({ PxTransform(_origin),v,Vector3(0,GRAVITY,0),DEFAULT_DAMPING,1,colorRGB[Blue],UNIFORM_LIFETIME }));
		}
	return list;
}
