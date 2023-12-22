#pragma once
#include "DynamicRigidBody.h"
class GameScene;
class Player :public DynamicRigidBody
{
public:
	Player(GameScene* scene,Vector3 pos, PxMaterial* mat,Color color,double radius,double mass,PxFilterData* filter);
	void handleMouse(int button, int state, int x, int y) override;
	void handleMotion(int x, int y)override;
	void update(double t)override;
	void keyPress(unsigned char key)override;
	void keyRelease(unsigned char key)override;
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;
private:
	struct Vector2 {
		double x;
		double y;
	};
	GameScene* scene;
	Vector2 originForce;
	char keyPressed;

	void die() override;
};

