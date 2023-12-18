#include "RigidBodySystem.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;

RigidBodySystem::RigidBodySystem(Scene* scene, const Vector3& g) :ParticleSystem(scene, g)
{
	//rigidBodyDemo();
}

void RigidBodySystem::update(double t)
{
	ParticleSystem::update(t);

	//crosshair.first->setPos(GetCamera()->getEye() + GetCamera()->getDir());
	//crosshair.first->setRot(-GetCamera()->getTransform().q);
	//crosshair.second->setPos(GetCamera()->getEye() + GetCamera()->getDir());
	//crosshair.second->setRot(-GetCamera()->getTransform().q);
}

void RigidBodySystem::keyPress(unsigned char key)
{
	switch (key) {
	case add_Uniwind:
		deleteForceGenerator(forceGenerators.back()); //OPCIONAL
		addForcetoAllParticlegenerators({ createForceGenerators<WindForceGenerator>(0.3, Vector3(30, 20, 0)),gravityForce }); //FORMA1
		//addForcetoAllParticles({ createForceGenerators<WindForceGenerator>(0.3, Vector3(5,2, 0)) }); //FORMA2
		break;
	case add_Windwhirl:
		deleteForceGenerator(forceGenerators.back());
		addForcetoAllParticlegenerators({ createForceGenerators<WhirlwindsForceGenerator>(0.01, 1,Vector3(0,50, 0),7),gravityForce });
		//addForcetoAllParticles({ createForceGenerators<WhirlwindsForceGenerator>(0.01, 1,Vector3(0,-10,0),15) });
		break;
	case add_Explosion:
		deleteForceGenerator(forceGenerators.back());
		addForcetoAllParticlegenerators({ createForceGenerators<ExplosionForceGenerator>(Vector3(0,20,0), 200, 400000, 7),gravityForce });
		//addForcetoAllParticles({ createForceGenerators<ExplosionForceGenerator>(Vector3(0,0,0), 200, 400000, 7) });
		break;
	/*case '0':
		resetSystem();
		break;*/
	}
}

void RigidBodySystem::resetSystem()
{
	ParticleSystem::resetSystem();
	rigidBodyDemo();
}

void RigidBodySystem::rigidBodyDemo()
{
	//punto de mira
	crosshair = { new Particle(particleProperties[STATIC], true, PxGeometryType::eBOX, true, nullptr, { 0.01,0.002,0.001 }), new Particle(particleProperties[STATIC], true, PxGeometryType::eBOX, true, nullptr, { 0.002,0.01,0.001 }) };

	//suelo
	addParticles({ new StaticRigidBody(particleProperties[STATIC], nullptr, PxGeometryType::eBOX, { 200,1,200 }) });

	auto gen = createGenerator<GaussianParticleGenerator>(true, new DynamicRigidBody({ PxTransform(0,100,0),{ 5,5,5 },DEFAULT_DAMPING,20,1,colorRGB[TransparentPink],15,0,NONE }, false, nullptr, PxGeometryType::eBOX, { 3,3,3 }), DefaultEffect, { 50,50,50 }, 20, 30);
	gen->setGenProb(0.1);
	gen->setNParticles(1);

	auto gen2 = createGenerator<SimpleParticleGenerator>(true, new DynamicRigidBody({ PxTransform(0,100,0),{ 5,5,5 },DEFAULT_DAMPING,80,3,colorRGB[Yellow],15,0,NONE }, false, nullptr), DefaultEffect, { 50,50,50 }, 20, 30);
	gen2->setGenProb(0.1);
	gen2->setNParticles(1);

	auto gen3 = createGenerator<GaussianParticleGenerator>(true, new DynamicRigidBody({ PxTransform(0,100,0),{ 5,5,5 },DEFAULT_DAMPING,30,1,colorRGB[Blue],15,0,NONE }, false, nullptr, PxGeometryType::eBOX, { 1,10,1 }, { 1000,0,0 }), DefaultEffect, { 50,50,50 }, 20, 30);
	gen3->setGenProb(0.1);
	gen3->setNParticles(1);

}


