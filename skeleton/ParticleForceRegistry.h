#pragma once
#include "ForceGenerator.h"
#include <unordered_map>
using namespace std;

//typedef pair<ForceGenerator*, Particle*> FRPair;
using ForceMapIt = unordered_map<ForceGenerator*, list<Particle*>>::iterator;
using ParticlePosInForceMap = list<Particle*>::iterator;
using ParticleMapIt = unordered_map<Particle*, list<pair<ForceGenerator*, ParticlePosInForceMap>>>::iterator;
class ParticleForceRegistry
{
private:
	unordered_map<ForceGenerator*, list<Particle*>> forceMap;
	unordered_map<Particle*, list<pair<ForceGenerator*, ParticlePosInForceMap>>> particleMap;
public:

	ParticleForceRegistry() {}

	void updateForces(double t) {
		for (auto f_it: forceMap) {
			for (auto p : f_it.second)
				f_it.first->updateForce(p, t);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) {
		forceMap[fg].push_back(p);
		particleMap[p].push_back({ fg,next(forceMap[fg].end(), -1) });
	}
	void deleteParticleRegistry(Particle* p) { //cte por cada fuerza asociada 
		ParticleMapIt p_it;
		if ((p_it = particleMap.find(p)) == particleMap.end()) return;
		for (auto force_associated : (*p_it).second) { //recorre la lista de forces
			forceMap[force_associated.first].erase(force_associated.second);//deregistrar particula del forceGenerator
			if (forceMap[force_associated.first].empty())forceMap.erase(force_associated.first); //si forceGenerator ya no tiene particulas asociadas se borra
		}
		particleMap.erase(p_it); //deregistrar partícula del particleMap

	}
	void deleteForceRegistry(ForceGenerator* f) { // P*F=lineal
		ForceMapIt f_it;
		if ((f_it = forceMap.find(f)) == forceMap.end()) return;
		for (list<Particle*>::iterator p_it = (*f_it).second.begin(); p_it != (*f_it).second.end();++p_it) { //recorre la lista
			particleMap[*p_it].remove({f,p_it });//deregistrar force del particleMap
			if (particleMap[*p_it].empty())particleMap.erase(*p_it); //si particleMap ya no tiene force asociadas se borra
		}
		forceMap.erase(f_it); //deregistrar partícula del particleMap
	
	} 
};

