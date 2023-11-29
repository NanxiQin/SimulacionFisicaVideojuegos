#pragma once
#include "ForceGenerator.h"
class BuoyancyForceGenerator : public ForceGenerator
{

public:
	BuoyancyForceGenerator(Vector3 volume, double density = 10, double k1=0.1,Vector3 surfacePos = {0,0,0},Vector4 color=colorRGB[Blue], double gravity = -GRAVITY);
	~BuoyancyForceGenerator();

	void updateForce(Particle* particle, double t) override;

private:
	double density;
	double gravity;
	double k1;

	Particle* liquidParticle;
};

