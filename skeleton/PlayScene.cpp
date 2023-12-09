#include "PlayScene.h"

PlayScene::PlayScene() : Scene() {
	//addSystem(particleSys = new ParticleSystem(this, Vector3{ 0,GRAVITY,0}));
	addSystem(particleSysDemo = new ParticleSystemDemo(this, Vector3{ 0,GRAVITY,0}));
	addSystem(rigidBodySys = new RigidBodySystem(this, Vector3{ 0,GRAVITY,0}));

}



