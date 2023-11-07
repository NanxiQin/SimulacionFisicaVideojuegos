#include "Particle.h"
#include <iostream>

Particle::Particle(ParticleProperties properties, bool registerRender) : prop(properties), invMass(1 / properties.mass),forceAccum(0)
{
	if (registerRender)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(properties.radius)), &prop.transform, properties.color);
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
	prop.vel += resulting_accel * t; 

	//prop.vel += prop.acceleration * t; //ya no se usa
	prop.vel *= powf(prop.damping, t); //limitar la velocidad
	prop.transform.p += prop.vel * t; //multiplicar por t para no depender del deltaTime
	
	//cout << prop.transform.p.x<<" "<< prop.transform.p.y << " "<<  prop.transform.p.z << endl;

	if (prop.elapsedTime < prop.lifeTime)
		prop.elapsedTime += t;
	else alive = false;
	// Clear accum
	clearAccum();
}

