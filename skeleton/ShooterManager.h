#pragma once
#include "System.h"
#include "Particle.h"
class ShooterManager :public System {
private:
	int numProjectiles;
	void shoot(ParticleType type);
	double shoot_elapsedTime;
	bool shootEnable;
public:
	ShooterManager(Scene* scene);
	void update(double t);
	void keyPress(unsigned char key, const PxTransform& camera);
};

