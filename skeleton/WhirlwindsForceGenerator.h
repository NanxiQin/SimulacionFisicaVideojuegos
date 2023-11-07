#pragma once
#include "WindForceGenerator.h"
class WhirlwindsForceGenerator : public WindForceGenerator //depende de la posición del objeto
{
public:
	WhirlwindsForceGenerator(double k1, double K = 1,Vector3 origin = { 0,0,0 }, double duration = -1);
	virtual void updateForce(Particle* particle, double t);
protected:
	Vector3 origin;
	double K;
};

