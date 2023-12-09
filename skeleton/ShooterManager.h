#pragma once
#include "Particle.h"
class ParticleSystem;
class ShooterManager{
public:
	ShooterManager(ParticleSystem* system);
	void update(double t);
	void keyPress(unsigned char key);
private:
	template<class T>
	T* shoot(ParticleType type);
	double shoot_elapsedTime;
	bool shootEnable;
	ParticleSystem* system;
};

