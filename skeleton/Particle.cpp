#include "Particle.h"
#include <iostream>

Particle::Particle(ParticleProperties properties, bool registerRender, GeometryType geometryType, bool isStatic, PxMaterial* material, Vector3 volume) :
	prop(properties), invMass(1 / properties.mass), forceAccum(0), volume(volume), renderItem(nullptr), shape(nullptr), geometryType(geometryType), isStatic(isStatic), render(registerRender),material(material)
{
	if (fabs(invMass < 1e-10)) prop.damping = 0;
	createNewShape(geometryType);

}

Particle::~Particle() {
	die();
}

void Particle::die() {
	if (renderItem != nullptr)
		renderItem->release();
	if (shape != nullptr)
		shape = nullptr;
}

void Particle::registerRender()
{
	render = true;
	if (renderItem == nullptr)
		createNewRenderItem();
}

void Particle::setRadius(double r)
{
	if (geometryType != PxGeometryType::eSPHERE)return;
	prop.radius = r;
	createNewShape(geometryType);
}

void Particle::setVolume(Vector3 v)
{
	if (geometryType != PxGeometryType::eBOX)return;
	volume = v;
	createNewShape(geometryType);

}



void Particle::createNewRenderItem()
{
	if (!render) return;
	if (renderItem != nullptr) renderItem->release();
	renderItem = new RenderItem(shape, &prop.transform, prop.color);
}

Particle* Particle::clone(bool render) const
{
	return new Particle(prop, render); //no se registra el render
}

void Particle::update(double t) {

	if (prop.lifeTime != -1) {
		if (prop.elapsedTime < prop.lifeTime)
			prop.elapsedTime += t;
		else alive = false;
	}

	//if (isStatic)return;
	//// Get the accel considering the force accum
	Vector3 resulting_accel = forceAccum * invMass;
	prop.vel += resulting_accel * t;
	//prop.vel += prop.acceleration * t; //ya no se usa
	prop.vel *= powf(prop.damping, t); //limitar la velocidad
	prop.transform.p += prop.vel * t; //multiplicar por t para no depender del deltaTime

	// Clear accum
	clearAccum();
}

