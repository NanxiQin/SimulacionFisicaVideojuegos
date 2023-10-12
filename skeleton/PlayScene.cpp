#include "PlayScene.h"

PlayScene::PlayScene() : Scene(), shooterMng(new ShooterManager(this)) {
	addSystem(shooterMng=new ShooterManager(this));
	addSystem(particleSys = new ParticleSystem(this, Vector3{ 0,GRAVITY,0}));

}



