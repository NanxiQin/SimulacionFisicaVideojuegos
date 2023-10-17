#pragma once
#include "Entity.h"

using namespace physx;
using namespace std;
class Particle:public Entity
{
public:
	
	Particle(ParticleProperties properties);
	ParticleProperties prop;
	virtual ~Particle();
	virtual void update(double t)override;
	
	//void setPosition(Vector3 position) { trans.p = position; };

	inline Vector3& getPos() { return prop.transform.p; };
	inline PxQuat& getRot() { return prop.transform.q; };
	inline Vector3& getVel() { return prop.vel; };
	inline ParticleType getType() { return prop.type; };

	void setLifeTime(double lifeTime_) { prop.lifeTime = lifeTime_; }
	
	ParticleProperties getProp();

	void die() override;

	//DUDA: A BORRAR
	/*virtual Particle* clone()const;*/

protected:

	RenderItem* renderItem;
	double invMass;

};

