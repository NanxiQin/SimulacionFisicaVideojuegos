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
public:
	virtual void updateForce(Particle* particle,double t) = 0;
	ForceGeneratorType _name;
	double _t = 0.0; // If starting negative --> eternal
	double _duration = -1e10;
	inline bool updateTime(double t) {
		_t += t;
		return _t < _duration || _duration < 0.0; // Devuelve true si ya era cero o si es positivo
	}
	virtual ~ForceGenerator() {}
};
