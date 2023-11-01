#include "Particle.h"
#include <iostream>

Particle::Particle(ParticleProperties properties, bool registerRender) : prop(properties), invMass(1 / properties.mass),forceAccum(0)
{
	if (registerRender)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(properties.mass)), &prop.transform, properties.color);
	else renderItem = nullptr;
}

Particle::~Particle() {
	die();
}

void Particle::die() {
	if (renderItem != nullptr)
		renderItem->release();
}

void Particle::registerRender()
{
	if (renderItem == nullptr)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(prop.mass)), &prop.transform, prop.color);
}

Particle* Particle::clone(bool render) const
{
	return new Particle(prop, render); //no se registra el render
}

void Particle::update(double t) {
	//// Get the accel considering the force accum
	Vector3 resulting_accel = forceAccum * invMass;
	prop.vel += resulting_accel * t; // Ex. 1.3 --> add 

	prop.vel += prop.acceleration * t; //incrementar velocidad según aceleración
	prop.vel *= powf(prop.damping, t); //limitar la velocidad
	prop.transform.p += prop.vel * t; //multiplicar por t para no depender del deltaTime
	if (prop.elapsedTime < prop.lifeTime)
		prop.elapsedTime += t;
	else alive = false;
	// Clear accum
	clearAccum();
}

