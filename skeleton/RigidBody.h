#pragma once
#include "Particle.h"
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;
using namespace std;
class RigidBody :public Particle
{
public:
	void update(double t)override;
	RigidBody* setEndColor(PxVec4 col);

protected:
	RigidBody(ParticleProperties prop, bool isStatic, PxMaterial* material, GeometryType geometryType= PxGeometryType::eSPHERE,Vector3 volume={1,1,1});
	//PxVec4 endColor;
};

