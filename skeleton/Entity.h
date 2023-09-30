#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "game_def.h"

using namespace physx;
using namespace game_def;
class Entity
{
public:
	virtual void update(double t) = 0;
	virtual ~Entity() {};
protected:
	Entity() {};
};

