#include "RubberBandForceGenerator.h"

RubberBandForceGenerator::RubberBandForceGenerator(Particle* other,double K, double restingLength, double maxLength) :
	SpringForceGenerator(other, K, restingLength, maxLength) 
{
	type = RubberBand;
}

void RubberBandForceGenerator::updateForce(Particle* p, double t)
{
	Vector3 rel_pos = other->getPos() - p->getPos();
	if (rel_pos.magnitude() > restingLength) {
		SpringForceGenerator::updateForce(p, t);
	}
}
