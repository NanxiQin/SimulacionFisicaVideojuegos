#include "DynamicRigidBody.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;

DynamicRigidBody::DynamicRigidBody(ParticleProperties prop, bool registerRendering, PxMaterial* material, GeometryType geometryType, Vector3 volume, Vector3 tensor, PxFilterData filter) :
	RigidBody(prop, false, material, geometryType, volume), body(nullptr), material(material),tensor(tensor),filter(filter)
{
	shape->setSimulationFilterData(filter);
	body = gPhysics->createRigidDynamic(PxTransform(prop.transform.p));

	body->setLinearVelocity(prop.vel);
	body->setLinearDamping(prop.damping);
	body->setAngularVelocity({ 0,0,0 });

	body->attachShape(*shape);

	gScene->addActor(*body);
	//body->setWakeCounter(100000);
	if (registerRendering) registerRender();
	if (tensor != Vector3(-1, -1, -1)) setTensor(tensor);
	else PxRigidBodyExt::setMassAndUpdateInertia(*body, prop.mass);

}
void DynamicRigidBody::die()
{
	Particle::die();
	if (body != nullptr) {
		body->release();
		body = nullptr;
	}
}

DynamicRigidBody* DynamicRigidBody::clone(bool render) const
{
	return new DynamicRigidBody(prop, render, material, geometryType, volume,tensor,filter);
}

void DynamicRigidBody::createNewRenderItem()
{
	if (!render) return;
	if (renderItem != nullptr) renderItem->release();
	renderItem = new RenderItem(shape, body, prop.color);
}

void DynamicRigidBody::registerRender()
{
	render = true;
	if (renderItem == nullptr)
		createNewRenderItem();
}

void DynamicRigidBody::setTensor(Vector3 t)
{
	body->setMassSpaceInertiaTensor(t);
}
