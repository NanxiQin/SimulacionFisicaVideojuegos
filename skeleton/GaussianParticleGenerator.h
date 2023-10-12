#pragma once
#include "ParticleGenerator.h"
class GaussianParticleGenerator :public ParticleGenerator
{
public:
	GaussianParticleGenerator(Vector3 pos, Vector3 vel);
	list<Particle*>generateParticles() override;

private:
	Vector3 pos, vel;
	normal_distribution<double> normal_dis{ NORMAL_MEAN,NORMAL_SIGMA }; //base para generar números normales

};

