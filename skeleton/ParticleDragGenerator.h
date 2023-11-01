#pragma once
#include "ForceGenerator.h"
class ParticleDragGenerator :public ForceGenerator
{
public:
	ParticleDragGenerator();
	ParticleDragGenerator(const float k1, const float k2);
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(float k1_, float k2_) { k1 = k1_; k2 = k2_; }
	inline float getK1() { return k1; }
	inline float getK2() { return k2; }
protected:
	float k1; //coef vel
	float k2; //coef square vel

};

