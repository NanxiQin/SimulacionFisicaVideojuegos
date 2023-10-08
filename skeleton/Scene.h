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
	virtual void keyPress(unsigned char key, const PxTransform& camera) ;
	void addSystem(System* s);
};

