#include "Firework.h"

Particle* Firework::clone(bool render) const
{
	return new Firework(prop,nullptr, n_gen,render,setRandomColor);
}

list<Particle*> Firework::explode()
{
	if (n_gen > FIREWORK_MAX_GEN ) return{};
	
	gen->setParticle(this,true);
	
	//2 FORMAS
	setRandomColor? gen->setRandomColor(): gen->setColor(colorRGB[n_gen % COLOR_SIZE]);

	gen->resetElapsedTime();
	return gen->generateParticles();
}
