#pragma once
#include "DynamicRigidBody.h"
class Player :public DynamicRigidBody
{
	struct Vector2 {
		double x;
		double y;
	};
public:
	Player(Vector3 pos,Color color,double radius,double mass);
	void handleMouse(int button, int state, int x, int y) override;
	void handleMotion(int x, int y)override;
	void update(double t)override;
private:
	Vector2 originForce;

};

