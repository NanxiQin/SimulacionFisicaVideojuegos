#include "RigidBodySystem.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;

RigidBodySystem::RigidBodySystem(Scene* scene, const Vector3& g) :ParticleSystem(scene, g)
{
	rigidBodyDemo();
}

void RigidBodySystem::update(double t)
{
	ParticleSystem::update(t);

	crosshair.first->setPos(GetCamera()->getEye() + GetCamera()->getDir());
	crosshair.first->setRot(-GetCamera()->getTransform().q);
	crosshair.second->setPos(GetCamera()->getEye() + GetCamera()->getDir());
	crosshair.second->setRot(-GetCamera()->getTransform().q);
}

void RigidBodySystem::rigidBodyDemo()
{
	//punto de mira
	crosshair = { new Particle(particleProperties[STATIC], true, PxGeometryType::eBOX, true, nullptr, { 0.02,0.004,0.001 }), new Particle(particleProperties[STATIC], true, PxGeometryType::eBOX, true, nullptr, { 0.004,0.02,0.001 }) };
	
	//suelo
	addParticles({ new StaticRigidBody(particleProperties[STATIC], nullptr, PxGeometryType::eBOX, { 200,20,200 }) });

	auto gen = createGenerator<GaussianParticleGenerator>(true, new DynamicRigidBody({ PxTransform(0,100,0),{ 5,5,5 },DEFAULT_DAMPING,0.01,1,colorRGB[Red],15,0,NONE }, false, nullptr, PxGeometryType::eBOX, { 5,5,5 }), DefaultEffect, { 50,50,50 }, 20, 30);
	gen->setGenProb(0.01);
	gen->setNParticles(1);

	auto gen2 = createGenerator<SimpleParticleGenerator>(true, new DynamicRigidBody({ PxTransform(0,100,0),{ 5,5,5 },DEFAULT_DAMPING,20,3,colorRGB[Yellow],15,0,NONE }, false, nullptr), DefaultEffect, { 50,50,50 }, 20, 30);
	gen2->setGenProb(0.01);
	gen2->setNParticles(1);

	auto gen3 = createGenerator<GaussianParticleGenerator>(true, new DynamicRigidBody({ PxTransform(0,100,0),{ 5,5,5 },DEFAULT_DAMPING,0.01,1,colorRGB[Pink],15,0,NONE }, false, nullptr, PxGeometryType::eBOX, { 0.5,10,0.5 }, { 1000,0,0 }), DefaultEffect, { 50,50,50 }, 20, 30);
	gen3->setGenProb(0.01);
	gen3->setNParticles(1);

}


