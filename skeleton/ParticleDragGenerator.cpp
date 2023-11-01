#include "ParticleDragGenerator.h"

ParticleDragGenerator::ParticleDragGenerator() :ForceGenerator(),k1(0),k2(0)
{
}

ParticleDragGenerator::ParticleDragGenerator(const float k1, const float k2) :ForceGenerator()
{
}

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	//si tiene masa infinita
	if (fabs(particle->getInvMass() < 1e-10)) return;

	Vector3 v = particle->getVel();
	float dragCoef = v.normalize();
	Vector3 dragF;
	dragCoef = k1 * dragCoef + k2 * dragCoef * dragCoef;
	dragF = -v * dragCoef;
	particle->addForce(dragF);
}
