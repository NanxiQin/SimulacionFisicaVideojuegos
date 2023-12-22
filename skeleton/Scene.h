#pragma once
#include "RenderUtils.hpp"
#include "Entity.h"
#include "System.h"
#include "game_def.h"
#include <list>

using namespace std;
class Scene
{
protected:
	Scene() {};
	list<System*>systems;

public:
	virtual ~Scene();
	virtual void update(double t);
	virtual void keyPress(unsigned char key) ;
	virtual void keyRelease(unsigned char key) ;
	virtual void handleMouse(int button, int state, int x, int y);
	virtual void handleMotion(int x, int y);
	virtual void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {};
	void addSystem(System* s);
};

