#include "SpringForceGenerator.h"
#include <iostream>
SpringForceGenerator::SpringForceGenerator(Particle* other, double K, double restingLength, double maxLength) :ForceGenerator(SpringForce), K(K), restingLength(restingLength), maxLength(maxLength), other(other) {}

void SpringForceGenerator::updateForce(Particle* p, double t)
{

	//si tiene masa infinita
	if (fabs(p->getInvMass()) < 1e-10) return;

	Vector3 rel_pos = other->getPos() - p->getPos();

	float length = rel_pos.normalize();
	float deltaX = length - restingLength;

	if (deltaX > maxLength) { //muelle roto
		alive = false;
		//cout << "Spring broken\n ";;
		return;
	}

	Vector3 force = rel_pos * deltaX * K;
	p->addForce(force);
}

void SpringForceGenerator::keyPress(unsigned char key)
{
	switch (key)
	{
	case increase:
		setK(K+5);
		break;
	case decrease:
		setK(K-5);
		break;
	}
}
