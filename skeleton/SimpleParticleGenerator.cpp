#include "SimpleParticleGenerator.h"
#include <random> 
#include <iostream>

SimpleParticleGenerator::SimpleParticleGenerator(GeneratorEffectProperties prop) :
	ParticleGenerator(prop.model, prop.originOffset,prop.minLifeTime,prop.maxLifeTime),
	uniform_x(uniform_real_distribution<double>{ prop.distribution.x.first, prop.distribution.x.second }),
	uniform_y(uniform_real_distribution<double>{ prop.distribution.y.first, prop.distribution.y.second }),
	uniform_z(uniform_real_distribution<double>{ prop.distribution.z.first, prop.distribution.z.second }) {}

list<Particle*> SimpleParticleGenerator::generateParticles()
{
	list<Particle*> list;
	if (checkGenerationProb()) //generar según prob
		//int color = rand() % COLOR_SIZE;
		for (int i = 0; i < _n_particles; ++i) {
			//ParticleProperties aux = modelParticleProp; //copia de las prop
			//aux.transform.p = generateRandomPos(modelParticleProp.transform.p);
			//aux.vel = Vector3(uniform_x(mt), uniform_y(mt), uniform_z(mt)) * _mean_velocity;
			//list.push_back(new Particle(aux));
			_model_particle->getPos() = generateRandomPos(_origin);
			_model_particle->getVel() = Vector3(uniform_x(mt), uniform_y(mt), uniform_z(mt)) * (_mean_velocity) ;
			setRandomLifeTime();
			list.push_back(_model_particle);
			_model_particle->registerRender();
			setParticle(_model_particle);
		}
	return list;
}
