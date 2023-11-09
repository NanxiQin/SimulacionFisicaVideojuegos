#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 origin, double radius, double K, double duration) : ForceGenerator(ExplosionForce,duration), origin(origin), radius(radius), maxRadius(radius), K(K) {}

void ExplosionForceGenerator::updateForce(Particle* particle, double t)
{
	//si tiene masa infinita
	if (fabs(particle->getInvMass() < 1e-10)) return;

	radius = (maxRadius / duration) * elapsedTime; //ve= maxRadius / duration

	double r = (particle->getPos() - origin).magnitude();//distancia de explosion
	if (r >= radius) return;
	if (r < 1e-10) r = 0.1; //para no dividir entre 0
	//si r<R	
	Vector3 f = (K / pow(r, 2)) * (particle->getPos() - origin) * exp(-elapsedTime / duration);
	particle->addForce(f);
}

