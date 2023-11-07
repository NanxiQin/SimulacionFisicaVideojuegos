#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 origin, double radius, double K, double duration) : ForceGenerator(duration), origin(origin), radius(radius), maxRadius(radius), K(K){}

void ExplosionForceGenerator::updateForce(Particle* particle, double t)
{
	//si tiene masa infinita
	if (fabs(particle->getInvMass() < 1e-10)) return;

	radius =(maxRadius / duration) * elapsedTime ; //ve= maxRadius / duration

	auto a = particle->getPos() - origin;
	double r = a.magnitude(); //distancia de explosion
	if (r < 1e-10) r = 0.1;
	if (r >= radius) return;
	//si r<R	
	Vector3 f = (K / pow(r, 2))* (particle->getPos() - origin) * exp(-elapsedTime / duration);
	particle->addForce(f);
}
