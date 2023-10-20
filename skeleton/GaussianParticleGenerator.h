#pragma once
#include "ParticleGenerator.h"
class GaussianParticleGenerator :public ParticleGenerator
{
public:
	GaussianParticleGenerator(GeneratorEffectProperties prop);
	list<Particle*>generateParticles() override;
	Vector3 generateNewDistribution()override;
private:
	normal_distribution<double> normal_x; //base para generar n�meros normales
	normal_distribution<double> normal_y;
	normal_distribution<double> normal_z; 

};

