#include "GameScene.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;

void GameScene::initGame()
{
	rigidBodySys->addParticles({ player = new Player({ 0,0,-200 }, Pink, 7, 1000) });
	GetCamera()->setEye(player->getPos()+Vector3(0,200,-50));
	GetCamera()->setDir(player->getPos()-GetCamera()->getEye() );
	GetCamera()->setEye(GetCamera()->getEye()+Vector3(0,0,50));
	//suelo
	
	rigidBodySys->addParticles({ new StaticRigidBody(particleProperties[STATIC], gPhysics->createMaterial(1.0f, 1.0f, 1.0f) , PxGeometryType::eBOX, { 150,1,600 })});
	rigidBodySys->addParticles({ backWall=new StaticRigidBody(particleProperties[STATIC], nullptr, PxGeometryType::eBOX, { 155,20,10 }) });
	backWall->setPos({ 0,0,GetCamera()->getEye().z -60});


	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			rigidBodySys->addParticles({ new DynamicRigidBody({ PxTransform(j*10,0,i*10),{ 0,0,0 },0.8,2,4,colorRGB[Yellow],-1,0,NONE }) });
		}
	}

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 4; j++) {
			rigidBodySys->addParticles({ new DynamicRigidBody({ PxTransform(j * 20-100,0,i * 20),{ 0,0,0 },0.8,2,9,colorRGB[Purple],-1,0,NONE }) });
		}
	}
}

GameScene::GameScene():Scene()
{
	addSystem(particleSys = new ParticleSystem(this, Vector3{ 0,GRAVITY,0 }));
	addSystem(rigidBodySys = new RigidBodySystem(this, Vector3{ 0,GRAVITY,0 }));
	rigidBodySys->setparticleBoundDistance({400,200,10000});
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


	GetCamera()->setEye((GetCamera()->getEye() + Vector3(0, 0, 20)*t));
	backWall->setPos({ 0,0,GetCamera()->getEye().z - 60 });
}

void GameScene::handleMotion(int x, int y)
{
	Scene::handleMotion(x, y);

	//GetCamera()->handleMotion(x, y);
}
