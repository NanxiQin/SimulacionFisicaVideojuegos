#pragma once
#include "Entity.h"

using namespace physx;

class Particle:public Entity
{
public:
	
	Particle(ParticleProperties properties);
	virtual ~Particle();
	virtual void update(double t)override;
	void die()override;
protected:
	Vector3 vel;
	Vector3 acceleration;
	const double damping;
	double lifeTime;
	double elapsedTime;
	PxTransform trans; //contiene pos y orientaci�n
	RenderItem* renderItem;

	ProjectileType type;
	double mass;
	double invMass;

};

