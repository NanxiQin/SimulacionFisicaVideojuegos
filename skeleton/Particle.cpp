#include "Particle.h"

Particle::Particle(ParticleProperties properties) :
	vel(properties.vel), trans(properties.trans), acceleration(properties.acceleration), damping(properties.damping), elapsedTime(0), lifeTime(PROJECTILE_LIFETIME), type(properties.type), mass(properties.mass), invMass(mass),
	renderItem(new RenderItem(CreateShape(PxSphereGeometry(properties.mass)), &trans, properties.color)){}

Particle::~Particle() {
	die();
}
void Particle::update(double t) {
	trans.p += vel * t; //multiplicar por t para no depender del deltaTime
	vel += acceleration * t; //incrementar velocidad según aceleración
	vel *= powf(damping, t); //limitar la velocidad
	if (elapsedTime < lifeTime)
		elapsedTime += t;
	else die();
}

void Particle::die() {
	DeregisterRenderItem(renderItem);
}
