#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "RigidBodySystem.h"
#include "Player.h"
class GameScene : public Scene
{
private:
	ParticleSystem* particleSys;
	RigidBodySystem* rigidBodySys;
	Player* player;
	Particle* backWall;
	Particle* rightWall;
	Particle* leftWall;
	void initGame();
	
public:
	GameScene();
	void handleMouse(int button, int state, int x, int y) override;
	void update(double t) override;
	void handleMotion(int x, int y)override;
};
