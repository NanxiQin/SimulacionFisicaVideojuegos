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
	ForceGenerator(ForceGeneratorType type,double duration = -1) :elapsedTime(0), duration(duration), alive(true),type(type){}
	double elapsedTime;
	double duration;// If starting negative --> eternal
	bool alive;
	ForceGeneratorType type;
public:
	inline void updateTime(double t) {
		elapsedTime += t;
		alive=(elapsedTime < duration || duration == -1); // Devuelve true si es eterno o que no llega a su tiempo límite
	}
	virtual void updateForce(Particle* particle, double t) = 0;
	virtual ForceGeneratorType getType() { return type; };
	bool isAlive() const { return alive; }
};
