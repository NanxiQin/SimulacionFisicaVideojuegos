#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "game_def.h"

using namespace physx;
using namespace game_def;
class Entity
{
protected:
	Entity():alive(true) {};
	bool alive;
public:
	virtual ~Entity() {};
	virtual void update(double t) = 0;
	virtual void die() {};
	inline void setAlive(bool alive_) { alive = alive_; }
	inline bool isAlive() { return alive; }
};

