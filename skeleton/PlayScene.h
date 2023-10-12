#pragma once
#include "Scene.h"
#include "ShooterManager.h"
#include "ParticleSystem.h"
using namespace std;
class PlayScene:public Scene
{
private:

	ShooterManager* shooterMng;
	ParticleSystem* particleSys;

public:
	PlayScene();

};

