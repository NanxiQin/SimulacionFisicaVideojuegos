#pragma once
#include "Scene.h"
#include "ParticleSystemDemo.h"
#include "RigidBodySystem.h"
using namespace std;
class DemoScene:public Scene
{
private:
	ParticleSystem* particleSys;
	ParticleSystemDemo* particleSysDemo;
	RigidBodySystem* rigidBodySys;
public:
	DemoScene();
	void handleMouse(int button, int state, int x, int y) override;
	void handleMotion(int x, int y)override;
	virtual void keyPress(unsigned char key);
};

