#pragma once
#include "ForceGenerator.h"
#include <unordered_map>
using namespace std;

typedef pair<ForceGenerator*, Particle*> FRPair;
class ParticleForceRegistry:public unordered_multimap<ForceGenerator*,Particle*>
{
public: 
	void updateForces(double t) {
		for (auto it = begin(); it != end(); ++it) {
			it->first->updateForce(it->second, t);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) { insert({ fg,p }); }
	void deleteParticleRegistry(Particle* p){} //recorrer todo el mapa
	void deleteForceRegistry(ForceGenerator* f) { erase(f); } //recorrer todo el mapa
};

