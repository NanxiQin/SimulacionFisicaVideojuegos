#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) :vel(Vel), trans(Pos) {
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(2)), &trans, Vector4(1, 1, 1, 1));
}
Particle::~Particle() {
	renderItem->release();
}
void Particle::update(double t) {
	trans.p += vel * t;
}