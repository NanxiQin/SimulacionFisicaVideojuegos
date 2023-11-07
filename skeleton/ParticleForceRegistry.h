#pragma once
#include "ForceGenerator.h"
#include <unordered_map>
#include <unordered_set>
using namespace std;

class ParticleGenerator;
class ParticleForceRegistry
{
	using ParticleMapIt = unordered_map<Particle*, unordered_set<ForceGenerator*>>::iterator;
	using ParticleMapIt = unordered_map<Particle*, unordered_set<ForceGenerator*>>::iterator;
	using ParticleGenMapIt = unordered_map<ParticleGenerator*, unordered_set<ForceGenerator*>>::iterator;
	using ForceMapIt = unordered_map<ForceGenerator*, pair<unordered_set<ParticleGenerator*>, unordered_set<Particle*>>> ::iterator;
private:
	unordered_map<ForceGenerator*, pair<unordered_set<ParticleGenerator*>, unordered_set<Particle*>>> forceMap;
	unordered_map<Particle*, unordered_set<ForceGenerator*>> particleMap;
	unordered_map<ParticleGenerator*, unordered_set<ForceGenerator*>> particleGenMap;
public:

	ParticleForceRegistry() {}

	unordered_map<ForceGenerator*, pair<unordered_set<ParticleGenerator*>, unordered_set<Particle*>>>& ForceMap() { return forceMap; }
	unordered_map<Particle*, unordered_set<ForceGenerator*>>& ParticleMap() { return particleMap; };
	unordered_map<ParticleGenerator*, unordered_set<ForceGenerator*>>&ParticleGenMap() { return particleGenMap; };

	void updateForces(double t) {
		for (auto f_it : forceMap) {
			for (auto p : f_it.second.second)
				f_it.first->updateForce(p, t);
		}
	}

	void addParticleRegistry(ForceGenerator* fg, Particle* p) {
		forceMap[fg].second.insert(p);
		particleMap[p].insert({ fg });
	}

	void addParticleGenRegistry(ForceGenerator* fg, ParticleGenerator* g) {
		forceMap[fg].first.insert(g);
		particleGenMap[g].insert({ fg });
	}

	void deleteParticleRegistry(Particle* p) { //deregistrar particula (si este se borra)
		ParticleMapIt p_it;
		if ((p_it = particleMap.find(p)) == particleMap.end()) return;
		for (auto force_associated : (*p_it).second) { //recorre la lista de forces
			forceMap[force_associated].second.erase(p);//deregistrar particula del forceGenerator
		}
		particleMap.erase(p_it); //deregistrar partícula del particleMap

	}
	void deleteParticleGenRegistry(ParticleGenerator* g) { //deregistrar generador (si este se borra)
		ParticleGenMapIt g_it;
		if ((g_it = particleGenMap.find(g)) == particleGenMap.end()) return; //si no existe
		for (auto force_associated : (*g_it).second) { //recorre la lista de forces
			forceMap[force_associated].first.erase(g);//deregistrar generador del forceGenerator
		}
		particleGenMap.erase(g_it);

	}


	void deleteForceRegistryFromGen(ForceGenerator* f, ParticleGenerator* g) {//deregistrar fuerza de un gen concreto
		ParticleGenMapIt g_it;
		if ((g_it = particleGenMap.find(g)) == particleGenMap.end()) return; //si no existe
		(*g_it).second.erase(f);//deregistrar force del gen
	}


	void deleteForceRegistry(ForceGenerator* f) { //deregistrar fuerza (del sistema: particulas y generadores)
		ForceMapIt f_it;
		if ((f_it = forceMap.find(f)) == forceMap.end()) return;

		for (auto g_it : (*f_it).second.first) { //recorre la lista de forces
			particleGenMap[g_it].erase(f);//deregistrar particula del forceGenerator
		}

		for (auto p_it : (*f_it).second.second) { //recorre la lista de forces
			particleMap[p_it].erase(f);//deregistrar forceGenerator de la partícula
			if (particleMap[p_it].empty())particleMap.erase(p_it); //si las partículas ya no tiene fuerzas asociadas desaparece del map
		}
		forceMap.erase(f_it); //deregistrar partícula del particleMap

	}
};

