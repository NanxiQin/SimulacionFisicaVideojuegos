#include "GravityForceGenerator.h"
#include <math.h>
GravityForceGenerator::GravityForceGenerator(const Vector3& g):ForceGenerator(GravityForce), gravity(g){}

void GravityForceGenerator::updateForce(Particle* particle, double t)
{
	//si tiene masa infinita
	if (fabs(particle->getInvMass() < 1e-10)) return;

	//Apply the mass scaled gravity
	particle->addForce(gravity * particle->getMass());

}
