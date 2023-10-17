#include "ShooterManager.h"

ShooterManager::ShooterManager(Scene* scene) :System(scene), numProjectiles(0), shoot_elapsedTime(0), shootEnable(true) {}

void ShooterManager::update(double t) {
	System::update(t);
	if (!shootEnable) {
		shoot_elapsedTime += t;
		shootEnable= shoot_elapsedTime > SHOOT_CD;
	}
}
void ShooterManager::shoot(ParticleType type) {
	if (shootEnable) {
		shootEnable = false;
		shoot_elapsedTime = 0;

		ParticleProperties prop = particleProperties[type]; //coge las propiedades del proyectil según su tipo
		prop.vel = GetCamera()->getDir() * prop.vel; //orientation normalizado
		prop.transform = PxTransform(GetCamera()->getEye()); //orientation normalizado
		++numProjectiles;
		addEntity(new Particle(prop));

	}
}

void ShooterManager::keyPress(unsigned char key, const PxTransform& camera) {
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
