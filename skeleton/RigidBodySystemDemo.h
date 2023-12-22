#pragma once
#include "RigidBodySystem.h"
class RigidBodySystemDemo : public RigidBodySystem
{
public:
	RigidBodySystemDemo(Scene* scene, const Vector3& g = { 0.0f, GRAVITY, 0.0f });
	void update(double t) override;
	void keyPress(unsigned char key) override;
	void resetSystem() override;
private:
	void rigidBodyDemo();
	pair<Particle*, Particle*> crosshair;
};

