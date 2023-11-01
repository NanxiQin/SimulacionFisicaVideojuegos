#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g);
	virtual void updateForce(Particle* particle, double t);
	inline void setGravity(Vector3 g) { gravity = g; }

protected:
	Vector3 gravity;
};

