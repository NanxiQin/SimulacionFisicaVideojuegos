#include "WindForceGenerator.h"


WindForceGenerator::WindForceGenerator(double k1, Vector3 windVel, double duration, Vector3 windArea) :ForceGenerator(WindForce, duration), windVel(windVel), k1(k1), airDensity(1.2), dragCoef(0.5), k2(0.1), windArea(windArea) {}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	//si tiene masa infinita
	if (fabs(particle->getInvMass()) < 1e-10) return;

	auto pPos = particle->getPos();
	if (fabs(pPos.x) > windArea.x || fabs(pPos.y) > windArea.y || fabs(pPos.z) > windArea.z) return; //si est� fuera del �rea

	double areaEffe = 4 * PI * pow(particle->getRadius(), 2); //�rea efectiva del objeto que se enfrenta al viento 
	k2 = areaEffe * dragCoef * airDensity;

	Vector3 v = windVel - particle->getVel();
	// Apply the wind force
	Vector3 windF = (k1*v + k2 * abs(v.magnitude())*v);

	if (abs(windF.x) < 1e+06 && abs(windF.y) < 1e+06 && abs(windF.z) < 1e+06)
		particle->addForce(windF);

}
