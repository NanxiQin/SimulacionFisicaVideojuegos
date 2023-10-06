#pragma once
//#include "Scene.h"
#include "System.h"


class ShooterManager :public System
{
protected:
	int numProjectiles;
	void shoot(ProjectileType type);
	double shoot_elapsedTime;
	//Scene* scene;
	bool shootEnable;
	vector<Entity*>* grp_PROJECTILES;
public:
	constexpr static sysId id = _sys_SHOOTER;
	ShooterManager();
	void initSystem() override;
	void update(double t)override;
	void keyPress(unsigned char key)override;
};

