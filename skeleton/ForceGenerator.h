#pragma once
#include "RenderUtils.hpp"
#include "Entity.h"
#include "game_def.h"
#include <list>
#include "Particle.h"
#include <random> 
#include <iostream>
#include "core.hpp"
using namespace std;
using namespace game_def;
class ForceGenerator {
protected:
	ForceGenerator(double duration = -1) :elapsedTime(0), duration(duration), alive(true) {}
	double elapsedTime;
	double duration;// If starting negative --> eternal
	bool alive;
public:
	inline void updateTime(double t) {
		elapsedTime += t;
		alive=(elapsedTime < duration || duration == -1); // Devuelve true si es eterno o que no llega a su tiempo límite
	}
	virtual void updateForce(Particle* particle, double t) = 0;
	bool isAlive() const { return alive; }
};
