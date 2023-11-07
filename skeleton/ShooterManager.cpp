#include "ShooterManager.h"
#include "ParticleSystem.h"

ShooterManager::ShooterManager(ParticleSystem* system) :system(system), shoot_elapsedTime(0), shootEnable(true) {}

void ShooterManager::update(double t) {
	if (!shootEnable) {
		shoot_elapsedTime += t;
		shootEnable= shoot_elapsedTime > SHOOT_CD;
	}
}
Particle* ShooterManager::shoot(ParticleType type) {
	Particle* p = nullptr;
	if (shootEnable && particleNum[type] <= particleMaxNum[type]) {
		shootEnable = false;
		shoot_elapsedTime = 0;

		ParticleProperties prop = particleProperties[type]; //coge las propiedades del proyectil según su tipo
		prop.vel = GetCamera()->getDir() * prop.vel; //orientation normalizado
		prop.transform = PxTransform(GetCamera()->getEye()); //orientation normalizado
		system->addParticles({ p=new Particle(prop) });
	}
	return p;
}

void ShooterManager::keyPress(unsigned char key) {
	switch (key)
	{
	case shoot_Pistol:
		system->addGravity(shoot(PISTOL));
		break;
	case shoot_Artillery:
		system->addGravity(shoot(ARTILLERY));
		break;
	case shoot_Fireball:
		system->addFloating(shoot(FIREBALL));
		break;
	case shoot_Laser:
		shoot(LASER); //no acceleration
		break;
	default:
		break;
	}
}
