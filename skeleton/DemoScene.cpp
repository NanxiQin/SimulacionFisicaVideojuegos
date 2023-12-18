#include "DemoScene.h"

DemoScene::DemoScene() : Scene() {
	//addSystem(particleSys = new ParticleSystem(this, Vector3{ 0,GRAVITY,0}));
	addSystem(particleSysDemo = new ParticleSystemDemo(this, Vector3{ 0,GRAVITY,0}));
	addSystem(rigidBodySys = new RigidBodySystem(this, Vector3{ 0,GRAVITY,0}));

}

void DemoScene::handleMouse(int button, int state, int x, int y)
{
	Scene::handleMouse(button, state, x, y);
	GetCamera()->handleMouse(button, state, x, y);

}

void DemoScene::handleMotion(int x, int y)
{
	Scene::handleMotion(x, y);
	GetCamera()->handleMotion(x, y);
}



