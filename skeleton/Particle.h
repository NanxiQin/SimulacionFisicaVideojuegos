#pragma once
#include "Entity.h"

using namespace physx;
using namespace std;
class Particle :public Entity
{
public:

	Particle(ParticleProperties properties, bool registerRender = true);
	virtual ~Particle();

	void die() override;
	virtual void update(double t)override;
	virtual Particle* clone(bool render = true)const;
	virtual void registerRender();

	ParticleProperties getProp() const { return prop; };

	inline Vector3& getPos() { return prop.transform.p; };
	inline PxQuat& getRot() { return prop.transform.q; };
	inline Vector3& getVel() { return prop.vel; };
	inline ParticleType getType() const { return prop.type; };

	void setColor(Vector4 c) { prop.color = c;  if (renderItem != nullptr) renderItem->setColor(c); };

	void resetElapsedTime() { prop.elapsedTime = 0; };
	void setLifeTime(double lifeTime_) { prop.lifeTime = lifeTime_; }
	double getLifeTime() const { return prop.lifeTime; }

protected:

	ParticleProperties prop;
	RenderItem* renderItem;
	double invMass;

};

