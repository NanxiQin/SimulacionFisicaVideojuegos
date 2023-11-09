#include "Particle.h"
#include <iostream>

Particle::Particle(ParticleProperties properties, bool registerRender) : prop(properties), invMass(1 / properties.mass),forceAccum(0), renderItem(nullptr)
{
	if (registerRender)
		createNewRenderItem();
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
		createNewRenderItem();
}

void Particle::createNewRenderItem()
{
	if (renderItem != nullptr) delete renderItem;

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(prop.radius)), &prop.transform, prop.color);
}

Particle* Particle::clone(bool render) const
{
	return new Particle(prop, render); //no se registra el render
}

void Particle::update(double t) {
	//// Get the accel considering the force accum
	Vector3 resulting_accel = forceAccum * invMass;
	prop.vel += resulting_accel * t; 

	//prop.vel += prop.acceleration * t; //ya no se usa
	prop.vel *= powf(prop.damping, t); //limitar la velocidad
	prop.transform.p += prop.vel * t; //multiplicar por t para no depender del deltaTime
	
	if (prop.elapsedTime < prop.lifeTime)
		prop.elapsedTime += t;
	else alive = false;
	// Clear accum
	clearAccum();
}

