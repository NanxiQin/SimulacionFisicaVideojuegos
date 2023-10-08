#pragma once
#include "Entity.h"

using namespace physx;
using namespace std;
class Particle:public Entity
{
public:
	
	Particle(ParticleProperties properties);
	virtual ~Particle();
	virtual void update(double t)override;
	
	//void setPosition(Vector3 position) { trans.p = position; };

	inline Vector3& getPos() { return trans.p; };
	inline PxQuat& getRot() { return trans.q; };
	inline Vector3& getVel() { return vel; };

	void setLifeTime(double lifeTime_) { lifeTime = lifeTime_; }

	virtual Particle* clone()const;
protected:
	Vector3 vel;
	Vector3 acceleration;
	const double damping;
	double lifeTime;
	double elapsedTime;
	PxTransform trans; //contiene pos y orientación
	RenderItem* renderItem;
	Vector4 color;

	ProjectileType type;
	double mass;
	double invMass;

	void die() override;
};

