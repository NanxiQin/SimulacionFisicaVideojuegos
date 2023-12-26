#pragma once
#include "RigidBody.h"
class StaticRigidBody :public RigidBody
{
public:
	StaticRigidBody(ParticleProperties prop, PxMaterial* material, PxFilterData filter= filterDataOther, GeometryType geometryType = PxGeometryType::eSPHERE, Vector3 volume = { 1,1,1 });
	~StaticRigidBody() { die(); };
	void createNewRenderItem();
	inline Vector3 getPos()override { return body->getGlobalPose().p; };
	inline void setPos(Vector3 p)override { body->setGlobalPose(PxTransform{ p }); };
	void die() override;
	PxActor* getActor() { return body; }
private:
	PxRigidStatic* body;
};

