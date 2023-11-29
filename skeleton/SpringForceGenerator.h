#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
#include <cmath>

class SpringForceGenerator : public ForceGenerator
{
protected:
	double K;
	double restingLength;
	double maxLength;
	Particle* other;
public:
	SpringForceGenerator(Particle* other, double K, double restingLength, double maxLength = 1000);

	void updateForce(Particle* p, double t) override;
	void keyPress(unsigned char key)override;
	inline void setK(double d) { K = d; if (K < 0)K = 0; cout << "Spring K: " << K << endl; }
};