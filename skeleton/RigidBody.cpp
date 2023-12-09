#include "RigidBody.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;

RigidBody::RigidBody(ParticleProperties prop,bool isStatic,PxMaterial* material, GeometryType geometryType, Vector3 volume) :Particle(prop, false, geometryType, isStatic,material, volume)
{}


void RigidBody::update(double t)
{
	if (prop.lifeTime != -1) {
		if (prop.elapsedTime < prop.lifeTime)
			prop.elapsedTime += t;
		else alive = false;
	}
	
}

RigidBody* RigidBody::setEndColor(PxVec4 col)
{
	return nullptr;
}
