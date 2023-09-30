#pragma once
#include "Entity.h"

using namespace physx;

class Particle:public Entity
{
public:
	
	Particle(ParticleProperties properties);
	virtual ~Particle();
	virtual void update(double t)override;
protected:
	Vector3 vel;
	Vector3 acceleration;
	const double damping;
	double lifeTime;
	double elapsedTime;
	PxTransform trans; //contiene pos y orientación
	RenderItem* renderItem;

	ProjectileType type;
	double mass;
	double invMass;

	void die();
};

