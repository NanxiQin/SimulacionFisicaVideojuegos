#pragma once
#include "Scene.h"
class ShooterManager
{
private:
	int numProjectiles;
	void shoot(ProjectileType type);
	double shoot_elapsedTime;
	Scene* scene;
	bool shootEnable;
public:
	ShooterManager(Scene* scene);
	void update(double t);
	void keyPress(unsigned char key, const PxTransform& camera);
};

