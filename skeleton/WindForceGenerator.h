#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator
{
public:
	WindForceGenerator(double k1 = 0, Vector3 windVel = { 0,0,0 },double duration=-1);
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(double k1_) { k1 = k1_; }
	inline double getK1() { return k1; }
protected:
	Vector3 windVel;
	
	const double airDensity;
	const double dragCoef;
	double k1; //coef rozamiento vel
	double k2; //coef square vel

};

