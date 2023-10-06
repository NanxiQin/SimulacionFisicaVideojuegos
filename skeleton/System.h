#pragma once
#include "game_def.h"
#include "RenderUtils.hpp"
#include "Entity.h"
using namespace game_def;
using namespace std;
class Manager;
class System
{
public:
	System() :mngr_(nullptr) {}
	virtual ~System() { }
	void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	virtual void initSystem() { }
	virtual void update(double t) { }
	virtual void keyPress(unsigned char key) {};

protected:
	Manager* mngr_;
};