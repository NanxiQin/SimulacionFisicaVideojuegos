#pragma once
#include "Scene.h"
#include "ParticleSystemDemo.h"
#include "RigidBodySystem.h"
using namespace std;
class PlayScene:public Scene
{
private:

	ParticleSystem* particleSys;
	ParticleSystemDemo* particleSysDemo;
	RigidBodySystem* rigidBodySys;
public:
	PlayScene();

};

