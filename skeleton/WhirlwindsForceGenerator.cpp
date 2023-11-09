#include "WhirlwindsForceGenerator.h"

WhirlwindsForceGenerator::WhirlwindsForceGenerator(double k1, double K , Vector3 origin, double duration) :WindForceGenerator(k1,{ 0,0,0 },duration), origin(origin), K(K)
{
	type = WindWhirlForce;
}

void WhirlwindsForceGenerator::updateForce(Particle* particle, double t)
{	
	auto pVel = particle->getPos();
	windVel = K * Vector3(origin.z- pVel.z, 50 + origin.y -pVel.y, pVel.x - origin.x);
	
	WindForceGenerator::updateForce(particle, t);

}
