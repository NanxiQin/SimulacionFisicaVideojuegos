#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(GeneratorEffectProperties prop):
	ParticleGenerator(prop.model, prop.originOffset),
	normal_x(normal_distribution<double>{ prop.distribution.x.first, prop.distribution.x.second }),
	normal_y(normal_distribution<double>{ prop.distribution.y.first, prop.distribution.y.second }),
	normal_z(normal_distribution<double>{ prop.distribution.z.first, prop.distribution.z.second })
{}
list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> list;
	if (checkGenerationProb()) //generar según prob
		//int color = rand() % COLOR_SIZE;
		for (int i = 0; i < _n_particles; ++i) {
			ParticleProperties aux = modelParticleProp; //copia de las prop
			aux.transform.p = generateRandomPos(_origin);
			aux.vel = Vector3(normal_x(mt), normal_y(mt), normal_z(mt)) * _mean_velocity;
			list.push_back(new Particle(aux));
				}
	return list;
}
