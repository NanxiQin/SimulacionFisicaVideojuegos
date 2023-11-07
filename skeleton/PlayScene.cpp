#include "PlayScene.h"

PlayScene::PlayScene() : Scene() {
	addSystem(particleSys = new ParticleSystem(this, Vector3{ 0,GRAVITY,0}));

}



