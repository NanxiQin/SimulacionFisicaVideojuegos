#include "PlayScene.h"

PlayScene::PlayScene() : Scene(), shooterMng(new ShooterManager(this)) {
	addSystem(shooterMng=new ShooterManager(this));
}

