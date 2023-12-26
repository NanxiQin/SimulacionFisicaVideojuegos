#pragma once
#include <unordered_map>
#include <fstream> //para leer fichero
#include "Scene.h"
#include "ParticleSystem.h"
#include "RigidBodySystem.h"
#include "Player.h"
class GameScene : public Scene
{

	enum State{ preparing,pausing,playing,restart,win,lose};
public:
	GameScene();

	void update(double t) override;
	void handleMouse(int button, int state, int x, int y) override;
	virtual void keyPress(unsigned char key);
	void handleMotion(int x, int y)override;
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)override;
	
	void onPlayerLose();
	void onPlayerWin();
	void onRestart();
	void onPlaying();
	void shootFireworks();

	bool rigidBodyExists(PxActor* actor, RigidBody* & rb);
private:

	double roadWidth;
	double roadLength;
	Vector3 metaPos;
	unordered_map<PxActor*, RigidBody*> actorMap;

	ParticleSystem* particleSys;
	RigidBodySystem* rigidBodySys;
	RigidBodySystem* roadSys;
	Player* player;
	Particle* backWall;
	Particle* rightWall;
	Particle* leftWall;
	WindForceGenerator* windForce;
	SimpleParticleGenerator* constrail;
	double counter;
	State state;
	
	void initGame();
	void loadMap(const string& file);
	

};
