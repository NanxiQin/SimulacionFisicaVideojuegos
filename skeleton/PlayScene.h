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

};

