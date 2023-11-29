#pragma once
#include "Entity.h"
using namespace physx;
using namespace std;
using GeometryType = PxGeometryType::Enum;
class Particle :public Entity
{
public:

	Particle(ParticleProperties properties, bool registerRender = true, GeometryType geometryType = PxGeometryType::eSPHERE, bool isStatic = false);
	Particle(ParticleProperties properties, Vector3 volume, bool registerRender = true, GeometryType geometryType = PxGeometryType::eBOX, bool isStatic = false);
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
	inline double getVolume()const { return { volume.x * volume.y * volume.z }; };
	inline Vector3 getScale()const { return volume; };

	void setDamping(double damp) { prop.damping = damp; }
	void setStatic(bool _static) { isStatic = _static; };
	void setColor(Vector4 c) { prop.color = c;  if (renderItem != nullptr) renderItem->setColor(c); };
	void setMass(double mass) { prop.mass = mass; };
	void setRadius(double r);
	void setVolume(Vector3 v) ;

	void resetElapsedTime() { prop.elapsedTime = 0; };
	void setLifeTime(double lifeTime_) { prop.lifeTime = lifeTime_; }
	double getLifeTime() const { return prop.lifeTime; }

	inline void createNewShape(GeometryType type) {
		switch (type)
		{
		case PxGeometryType::eBOX:
			createNewShape<PxBoxGeometry>(volume.x, volume.y, volume.z);

			break;
		case PxGeometryType::eSPHERE:
			createNewShape<PxSphereGeometry>(prop.radius);
			break;

		}
	}

	template<class T, typename ...Ts>
	inline void createNewShape(Ts&&...args) {
		shape = CreateShape(T(forward<Ts>(args)...));
		geometryType = shape->getGeometryType();
		createNewRenderItem();
	}

	inline void addForce(Vector3 f) {
		forceAccum += f;
	}
protected:
	void createNewRenderItem();
	// Add force to apply in next integration only
	// Clears accumulated force
	inline void clearAccum() {
		forceAccum *= 0.0;
	}

	GeometryType geometryType;
	// Accumulated force
	Vector3 forceAccum;
	ParticleProperties prop;
	RenderItem* renderItem;
	PxShape* shape;
	Vector3 volume;
	double invMass;
	bool isStatic;
	bool render;

};

