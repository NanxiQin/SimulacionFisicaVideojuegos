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

		ProjectileInitProperties prop = projectileProperties[type]; //coge las propiedades del proyectil según su tipo
		Vector3 v = GetCamera()->getDir() * Vector3(prop.velocity, prop.velocity + prop.vertical_v, prop.velocity); //orientation normalizado
		++numProjectiles;
		addEntity(new Particle({ PxTransform(GetCamera()->getEye()),v,prop.acceleration,prop.damping,prop.mass,colorRGB[prop.color],PROJECTILE_LIFETIME,0,type }));

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
