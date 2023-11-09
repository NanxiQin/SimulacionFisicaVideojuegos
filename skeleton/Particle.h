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

	inline Vector3& getPos() { return prop.transform.p; };
	inline PxQuat& getRot() { return prop.transform.q; };
	inline Vector3& getVel() { return prop.vel; };
	inline ParticleType getType() const { return prop.type; };
	inline double getInvMass() const { return invMass; };
	inline double getMass() const { return prop.mass; };
	inline double getRadius()const { return prop.radius; };

	void createNewRenderItem();


	void setColor(Vector4 c) { prop.color = c;  if (renderItem != nullptr) renderItem->setColor(c); };
	void setMass(double mass) { prop.mass = mass; };
	void setRadius(double r) { prop.radius = r;  createNewRenderItem(); };

	void resetElapsedTime() { prop.elapsedTime = 0; };
	void setLifeTime(double lifeTime_) { prop.lifeTime = lifeTime_; }
	double getLifeTime() const { return prop.lifeTime; }

	// Add force to apply in next integration only
	inline void addForce(Vector3 f) {
		forceAccum += f;
	}
	// Clears accumulated force
	inline void clearAccum() {
		forceAccum *= 0.0;
	}
protected:

	// Accumulated force
	Vector3 forceAccum;
	ParticleProperties prop;
	RenderItem* renderItem;
	double invMass;


};

