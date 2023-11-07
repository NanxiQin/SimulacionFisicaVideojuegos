#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator : public ForceGenerator
{
public:
	ExplosionForceGenerator(Vector3 origin, double radius, double K, double duration);
	void updateForce(Particle* particle, double t) override;
private:
	PxVec3 origin;
	double radius;
	double maxRadius;
	double K; // intensidad de la explosión.
};

