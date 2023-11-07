#pragma once
#include "Particle.h"
class ParticleSystem;
class ShooterManager{
private:
	Particle* shoot(ParticleType type);
	double shoot_elapsedTime;
	bool shootEnable;
	ParticleSystem* system;
public:
	ShooterManager(ParticleSystem* system);
	void update(double t);
	void keyPress(unsigned char key);
};

