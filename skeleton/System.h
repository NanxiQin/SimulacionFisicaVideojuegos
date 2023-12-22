#pragma once
#include "RenderUtils.hpp"
#include "game_def.h"
#include <list>
using namespace std;
class Scene;

class System
{
protected:
	Scene* scene;
public:
	System(Scene* scene);
	~System();
	virtual void update(double t) {};
	virtual void keyPress(unsigned char key) {};
	virtual void keyRelease(unsigned char key) {};
	virtual void handleMouse(int button, int state, int x, int y) {};
	virtual void handleMotion(int x, int y) {};
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {};

};

