#include "Particle.h"

Particle::Particle(ParticleProperties properties) : prop(properties), invMass(1/properties.mass),
	renderItem(new RenderItem(CreateShape(PxSphereGeometry(properties.mass)), &prop.transform, properties.color)){}

Particle::~Particle() {
	die();
}
void Particle::update(double t) {
	prop.transform.p += prop.vel * t; //multiplicar por t para no depender del deltaTime
	prop.vel += prop.acceleration * t; //incrementar velocidad según aceleración
	prop.vel *= powf(prop.damping, t); //limitar la velocidad
	if (prop.elapsedTime < prop.lifeTime)
		prop.elapsedTime += t;
	else alive=false;
}

//Particle* Particle::clone() const
//{
//	return new Particle(prop);
//}

ParticleProperties Particle::getProp()
{
	return prop;
}

void Particle::die() {
	renderItem->release();
}
