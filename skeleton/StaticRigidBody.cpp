#include "StaticRigidBody.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;

StaticRigidBody::StaticRigidBody(ParticleProperties prop, PxMaterial* material, PxFilterData filter, GeometryType geometryType, Vector3 volume) :RigidBody(prop, true, material, geometryType, volume)
{
	shape->setSimulationFilterData(filter);
	body = gPhysics->createRigidStatic(PxTransform(prop.transform.p));
	body->attachShape(*shape);
	render = true;
	createNewRenderItem();
	gScene->addActor(*body);
}

void StaticRigidBody::die()
{
	Particle::die();
	if (body != nullptr)
		body->release();
}

void StaticRigidBody::createNewRenderItem()
{
	if (!render) return;
	if (renderItem != nullptr) renderItem->release();
	renderItem = new RenderItem(shape, body, prop.color);
}

