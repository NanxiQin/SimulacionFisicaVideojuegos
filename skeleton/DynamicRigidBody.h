#pragma once
#include "RigidBody.h"
class DynamicRigidBody :public RigidBody
{
public:
	DynamicRigidBody(ParticleProperties prop, bool registerRendering=true,PxMaterial* material=nullptr, GeometryType geometryType = PxGeometryType::eSPHERE,Vector3 volume=Vector3(0), Vector3 tensor = Vector3(-1));
	void die() override;
	virtual DynamicRigidBody* clone(bool render = true)const;
	void createNewRenderItem();;
	void registerRender()override;
	inline Vector3 getPos()override { return body->getGlobalPose().p; } ;
	inline void setPos(Vector3 p)override { body->setGlobalPose(PxTransform{ p }); };
	inline Vector3 getVel()override { return body->getLinearVelocity(); } ;
	inline void setVel(Vector3 v)override { body->setLinearVelocity(v); };
	void setTensor(Vector3 t);
private:
	PxRigidDynamic* body;
	PxMaterial* material;
};

