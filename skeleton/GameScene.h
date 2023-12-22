#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "RigidBodySystem.h"
#include "Player.h"
#include <unordered_map>
class GameScene : public Scene
{
public:
	GameScene();
	void handleMouse(int button, int state, int x, int y) override;
	virtual void keyPress(unsigned char key);
	void update(double t) override;
	void handleMotion(int x, int y)override;
	void onPlayerDie();
	bool dynamicRigidBodyExists(PxActor* actor, DynamicRigidBody* & rb);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)override;
private:
	unordered_map<PxActor*, DynamicRigidBody*> actorMap;

	ParticleSystem* particleSys;
	RigidBodySystem* rigidBodySys;
	Player* player;
	Particle* backWall;
	Particle* rightWall;
	Particle* leftWall;
	SimpleParticleGenerator* rail;
	bool active;
	void initGame();
	

};
