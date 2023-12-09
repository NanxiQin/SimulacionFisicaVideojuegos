#pragma once
#include "RenderUtils.hpp"
#include "Entity.h"
#include "game_def.h"
#include <list>
using namespace std;
class Scene;

class System
{
protected:
	Scene* scene;
	list<Entity*> entities;
	void refresh();
public:
	System(Scene* scene);
	~System();
	virtual void update(double t);
	virtual void keyPress(unsigned char key) {};
	void addEntity(Entity* e);

};

