#include "WhirlwindsForceGenerator.h"

WhirlwindsForceGenerator::WhirlwindsForceGenerator(double k1, double K , Vector3 origin, double duration) :WindForceGenerator(k1,{ 0,0,0 },duration), origin(origin), K(K)
{
	type = WindWhirlForce;
}

void WhirlwindsForceGenerator::updateForce(Particle* particle, double t)
{	
	auto pos = particle->getPos();
	windVel = K * Vector3(origin.z- pos.z, 50 + origin.y - pos.y, pos.x - origin.x);
	
	WindForceGenerator::updateForce(particle, t);

}
