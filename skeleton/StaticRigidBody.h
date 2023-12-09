#pragma once
#include "RigidBody.h"
class StaticRigidBody :public RigidBody
{
public:
	StaticRigidBody(ParticleProperties prop, PxMaterial* material, GeometryType geometryType = PxGeometryType::eSPHERE, Vector3 volume = { 1,1,1 });
	void createNewRenderItem();
	void die() override;
private:
	PxRigidStatic* body;
};

