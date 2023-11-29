#pragma once
#include "SpringForceGenerator.h"
class RubberBandForceGenerator :public SpringForceGenerator
{
public:
	RubberBandForceGenerator(Particle* other,double K, double restingLength, double maxLength = 200);
	void updateForce(Particle* p, double t)override;
};

