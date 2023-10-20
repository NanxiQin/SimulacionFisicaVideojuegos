#pragma once
#include "Particle.h"
#include <list>
#include "ParticleGenerator.h"
class Firework :public Particle
{
public:
	Firework(ParticleProperties properties, ParticleGenerator*gen=nullptr,int nGen=0,bool registerRender =true,bool setRandomColor=false):
		Particle(properties,registerRender), gen(gen),n_gen(nGen), setRandomColor(setRandomColor){}
	
	virtual Particle* clone(bool render) const override;
	
	void addGenerator(ParticleGenerator* g) { gen = g; };
	
	// The firework generates more fireworks when exploding --> they should be gathered by the System
	list<Particle*> explode();

	int getNGen() const { return n_gen; }
	void setNGen(int n) { n_gen = n; }
private:
	
	ParticleGenerator* gen;
	int n_gen;
	bool setRandomColor;

};


