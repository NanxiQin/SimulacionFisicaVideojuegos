#include "BuoyancyForceGenerator.h"
#include <iostream>

BuoyancyForceGenerator::BuoyancyForceGenerator(Vector3 volume, double density, double k1, Vector3 surfacePos, Vector4 color, double gravity) :
	ForceGenerator(BuoyancyForce), density(density), k1(k1), liquidParticle(new Particle({ PxTransform(surfacePos), { 0,0,0 }, 10, 1e6,1, color, -1, 0, NONE }, true,PxGeometryType::eBOX,true,nullptr,{ volume.x,volume.y,volume.z })), gravity(gravity)
{
	liquidParticle->createNewShape<PxBoxGeometry>(nullptr,volume.x, volume.y, volume.z);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
	delete liquidParticle;
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t)
{
	//si tiene masa infinita
	if (fabs(particle->getInvMass()) < 1e-10) return;

	double h = particle->getPos().y;
	double h0 = liquidParticle->getPos().y;
	auto volume = particle->getVolume();
	auto height = particle->getScale().y;
	double immersed;
	Vector3 frictionForce = { 0,0,0 };

	if (h - h0 > height * 0.5) immersed = 0;
	else {
		if (h0 - h > height * 0.5) immersed = 1;
		else immersed = ((h0 - h) / height) + 0.5;
		/*frictionForce = k1 *(particle->getVel().getNormalized());*/
	}

	Vector3 buoyancyForce = { 0,(float)(density * volume * immersed * gravity),0 };
	particle->addForce(buoyancyForce - frictionForce);

}
