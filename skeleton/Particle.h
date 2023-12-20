#pragma once
#include "Entity.h"
using namespace physx;
using namespace std;
using GeometryType = PxGeometryType::Enum;
class Particle :public Entity
{
public:

	Particle(ParticleProperties properties, bool registerRender = true, GeometryType geometryType = PxGeometryType::eSPHERE, bool isStatic = false, PxMaterial* material =nullptr, Vector3 volume={1,1,1});
	virtual ~Particle();

	void die() override;
	void update(double t)override;
	virtual void handleMouse(int button, int state, int x, int y) {};
	virtual void handleMotion(int x, int y) {};

	virtual Particle* clone(bool render = true)const;
	virtual void registerRender();

	virtual inline Vector3 getPos() { return prop.transform.p; };
	virtual inline void setPos(Vector3 p) { prop.transform.p = p; };

	inline PxQuat getRot() { return prop.transform.q; };
	inline void setRot(PxQuat q) { prop.transform.q=q; };
	virtual inline Vector3 getVel() { return prop.vel; };
	virtual inline void setVel(Vector3 v) { prop.vel = v; };
	inline ParticleType getType() const { return prop.type; };
	inline double getInvMass() const { return invMass; };
	inline double getMass() const { return prop.mass; };
	inline double getRadius()const { return prop.radius; };
	inline double getVolume()const { return { volume.x * volume.y * volume.z }; };
	inline Vector3 getScale()const { return volume; };
	PxShape* getShape() { return shape; };

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
			createNewShape<PxBoxGeometry>(material,volume.x, volume.y, volume.z);

			break;
		case PxGeometryType::eSPHERE:
			createNewShape<PxSphereGeometry>(material,prop.radius);
			break;
			
		}
	}

	template<class T, typename ...Ts>
	inline void createNewShape(PxMaterial* mat,Ts&&...args) {
		shape = CreateShape(T(forward<Ts>(args)...), mat);
		geometryType = shape->getGeometryType();
		createNewRenderItem();
	}

	virtual inline void addForce(Vector3 f) {
		forceAccum += f;
	}
protected:
	virtual void createNewRenderItem();
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
	PxMaterial* material;
	double invMass;
	bool isStatic;
	bool render;

};

