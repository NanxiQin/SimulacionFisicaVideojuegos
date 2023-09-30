#include "PlayScene.h"

PlayScene::PlayScene() : Scene(), shooterMng(new ShooterManager(this)) {}

PlayScene::~PlayScene() {
	delete shooterMng;
}
void PlayScene::update(double t) {
	Scene::update(t);
	shooterMng->update(t);
}

void PlayScene::keyPress(unsigned char key, const PxTransform& camera) {
	Scene::keyPress(key,camera);
	shooterMng->keyPress(key, camera);
}

