#pragma once
#include "DynamicRigidBody.h"
class GameScene;
class Player :public DynamicRigidBody
{
public:
	Player(GameScene* scene,Vector3 pos, Vector3 metaPos, PxMaterial* mat,Color color,double radius,double mass,PxFilterData filter=filterDataOther);
	~Player() { die(); };

	void handleMouse(int button, int state, int x, int y) override;
	void handleMotion(int x, int y)override;
	void keyPress(unsigned char key)override;
	void keyRelease(unsigned char key)override;
	
	void update(double t)override;
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;
	void setActive() { active = true; };
private:
	struct Vector2 {
		double x;
		double y;
	};
	GameScene* scene;
	Vector2 originForce; //mouse pos
	char keyPressed;
	Vector3 metaPos;
	bool active;
	
	void die() override;
};

