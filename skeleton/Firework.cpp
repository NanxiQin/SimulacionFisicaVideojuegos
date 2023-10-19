#include "Firework.h"
#include <iostream>

//void Firework::die() {
//	explode();
//	Particle::die();
//}

Particle* Firework::clone(bool render) const
{
	return new Firework(prop,nullptr, n_gen,render);
}

list<Particle*> Firework::explode()
{
	cout << "NEW: " << n_gen << endl;
	if (n_gen > FIREWORK_MAX_GEN ) return{};
	//gen->setNewParticleProp(prop, false);
	
	gen->setParticle(this,true);
	gen->setMeanVelocity(gen->getInitMeanVelocity());
	
	//2 FORMAS
	//gen->setColor(colorRGB[n_gen%COLOR_SIZE]);
	gen->setRandomColor();

	gen->resetElapsedTime();
	return gen->generateParticles();
}
