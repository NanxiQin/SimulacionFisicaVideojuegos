#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle();
	void update(double t);
private:
	Vector3 vel;
	PxTransform trans; //contiene pos y orientación
	RenderItem* renderItem;
};

