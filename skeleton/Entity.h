#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "game_def.h"
class Manager;

using namespace physx;
using namespace game_def;
class Entity
{
protected:
	bool alive_;
	Manager* mngr_;
public:
	Entity();
	virtual void update(double t) {};
	virtual ~Entity() { die(); };

	inline void setContext(Manager* mngr) { mngr_ = mngr; };
	inline bool isAlive() { return alive_; }
	inline void setAlive(bool alive) { alive_ = alive; }
	virtual inline void die() {  }
};

