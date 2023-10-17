#include "Firework.h"

//void Firework::die() {
//	explode();
//	Particle::die();
//}

list<Particle*> Firework::explode()
{
	if (n_gen > FIREWORK_MAX_GEN) return{};
	gen->setNewParticleProp(prop, false);
	gen->setRandomColor();
	//gen->setMeanVelocity(gen->getMeanVelocity());
	gen->resetElapsedTime();
	return gen->generateParticles();
}
