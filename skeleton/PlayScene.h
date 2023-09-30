#pragma once
#include "Scene.h"
#include "ShooterManager.h"
using namespace std;
class PlayScene:public Scene
{
private:

	ShooterManager* shooterMng;

public:
	PlayScene();
	~PlayScene();
	void update(double t)override;
	void keyPress(unsigned char key, const PxTransform& camera)override;

};

