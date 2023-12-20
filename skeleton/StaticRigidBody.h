#pragma once
#include "RigidBody.h"
class StaticRigidBody :public RigidBody
{
public:
	StaticRigidBody(ParticleProperties prop, PxMaterial* material, PxFilterData* filter=nullptr, GeometryType geometryType = PxGeometryType::eSPHERE, Vector3 volume = { 1,1,1 });
	void createNewRenderItem();
	inline Vector3 getPos()override { return body->getGlobalPose().p; };
	inline void setPos(Vector3 p)override { body->setGlobalPose(PxTransform{ p }); };
	void die() override;
private:
	PxRigidStatic* body;
};

