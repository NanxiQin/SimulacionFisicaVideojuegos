#include "WindForceGenerator.h"


WindForceGenerator::WindForceGenerator(double k1, Vector3 windVel, double duration ) :ForceGenerator(duration), windVel(windVel),k1(k1),airDensity(1.2),dragCoef(0.5),k2(0.1){}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	//si tiene masa infinita
	if (fabs(particle->getInvMass()) < 1e-10) return;
	
	double areaEffe = 4 *PI * pow(particle->getRadius(), 2); //área efectiva del objeto que se enfrenta al viento 
	//k2 = areaEffe * dragCoef* airDensity; //7.5?


	Vector3 v = windVel- particle->getVel();
	// Apply the wind force
	v -= particle->getVel(); // Wind velocity
	Vector3 windF = (k1 + k2 * v.magnitude()) * v;
	particle->addForce(windF);
}
