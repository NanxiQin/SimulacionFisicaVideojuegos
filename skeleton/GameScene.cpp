#include "GameScene.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;

// Define collision groups and masks
const PxU32 CollisionGroupWall = 1 << 0;      // Collision group for the wall
const PxU32 CollisionGroupSphereA = 1 << 1;   // Collision group for sphere A
const PxU32 CollisionGroupOther = 1 << 2;     // Collision group for other objects





void GameScene::initGame()
{



	// Set collision groups and masks for the static wall
	PxFilterData filterDataWall;
	filterDataWall.word0 = CollisionGroupWall;


	// Set collision groups and masks for sphere A
	PxFilterData filterDataSphereA;
	filterDataSphereA.word0 = CollisionGroupSphereA;
	
	// Set collision groups and masks for other objects
	PxFilterData filterDataOther;
	filterDataOther.word0 = CollisionGroupOther;

	rigidBodySys->addParticles({ player = new Player({ 0,0,-200 }, Pink, 7, 1000, &filterDataSphereA) });
	

	GetCamera()->setEye(player->getPos() + Vector3(0, 200, -50));
	GetCamera()->setDir(player->getPos() - GetCamera()->getEye());
	GetCamera()->setEye(GetCamera()->getEye() + Vector3(0, 0, 50));
	//suelo

	rigidBodySys->addParticles({ new StaticRigidBody(particleProperties[STATIC], gPhysics->createMaterial(0, 0, 0) ,&filterDataOther, PxGeometryType::eBOX, { 150,1,600 }) });
	rigidBodySys->addParticles({ rightWall = new StaticRigidBody(particleProperties[STATIC], nullptr,&filterDataOther, PxGeometryType::eBOX, { 5,20,600}) });
	rightWall->setPos({ 150,0,0 });

	rigidBodySys->addParticles({ leftWall = new StaticRigidBody(particleProperties[STATIC], nullptr,&filterDataOther, PxGeometryType::eBOX, { 5,20,600 }) });
	leftWall->setPos({ -150,0,0 });
	/*for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			rigidBodySys->addParticles({ new DynamicRigidBody({ PxTransform(j*10,0,i*10),{ 0,0,0 },0.8,2,4,colorRGB[Yellow],-1,0,NONE }) });
		}
	}*/

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			rigidBodySys->addParticles({ new DynamicRigidBody({ PxTransform(j * 20 - 100,0,i * 20),{ 0,0,0 },0.8,2,9,colorRGB[Purple],-1,0,NONE },true,nullptr,GeometryType::eSPHERE,{10,10,10}, Vector3(-1) ,&filterDataOther)});
			
		}
	}
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			rigidBodySys->addParticles({ new DynamicRigidBody({ PxTransform(j * 50 ,10,i * 50),{0,0,0},0.8,2,9,colorRGB[Blue],-1,0,NONE},true,nullptr,GeometryType::eBOX,{10,10,10}) });
		}
	}
	rigidBodySys->addParticles({ backWall = new StaticRigidBody(particleProperties[STATIC], nullptr,&filterDataWall, PxGeometryType::eBOX, { 155,20,10 }) });
	backWall->setPos({ 0,0,GetCamera()->getEye().z - 60 });
}

GameScene::GameScene() :Scene()
{
	addSystem(particleSys = new ParticleSystem(this, Vector3{ 0,GRAVITY,0 }));
	addSystem(rigidBodySys = new RigidBodySystem(this, Vector3{ 0,GRAVITY,0 }));
	rigidBodySys->setparticleBoundDistance({ 400,200,10000 });
	particleSys->setparticleBoundDistance({ 400,200,10000 });
	initGame();
}

void GameScene::handleMouse(int button, int state, int x, int y)
{
	Scene::handleMouse(button, state, x, y);

	//GetCamera()->handleMouse(button, state, x, y);
}

void GameScene::update(double t)
{
	Scene::update(t);


	GetCamera()->setEye((GetCamera()->getEye() + Vector3(0, 0, 20) * t));
	backWall->setPos({ 0,0,GetCamera()->getEye().z - 60 });
}

void GameScene::handleMotion(int x, int y)
{
	Scene::handleMotion(x, y);

	//GetCamera()->handleMotion(x, y);
}
