#include "ShooterManager.h"
#include "Manager.h"
ShooterManager::ShooterManager() : numProjectiles(0), shoot_elapsedTime(0), shootEnable(true) {}

void ShooterManager::update(double t) {
	if (!shootEnable) {
		shoot_elapsedTime += t;
		shootEnable= shoot_elapsedTime > SHOOT_CD;
	}
}
void ShooterManager::shoot(ProjectileType type) {
	if (shootEnable) {
		shootEnable = false;
		shoot_elapsedTime = 0;

		ProjectileInitProperties prop = particleProperties[type]; //coge las propiedades del proyectil según su tipo
		Vector3 v = GetCamera()->getDir() * Vector3(prop.velocity, prop.velocity + prop.vertical_v, prop.velocity); //orientation normalizado
		++numProjectiles;
		mngr_->addEntity(_grp_PROJECTILES);
		//scene->addEntity(new Particle({ GetCamera()->getEye(),v,prop.acceleration,prop.damping,prop.mass,colorRGB[prop.color] }));

	}
}

void ShooterManager::initSystem() {
	
	grp_PROJECTILES = mngr_->getGroup(_grp_PROJECTILES);
	


}

void ShooterManager::keyPress(unsigned char key) {
	switch (key)
	{
	case shoot_Pistol:
		shoot(PISTOL);
		break;
	case shoot_Artillery:
		shoot(ARTILLERY);
		break;
	case shoot_Fireball:
		shoot(FIREBALL);
		break;
	case shoot_Laser:
		shoot(LASER);
		break;
	default:
		break;
	}
}
