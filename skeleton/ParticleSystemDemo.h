#pragma once
#include "ParticleSystem.h"
class ParticleSystemDemo : public ParticleSystem
{
public:
	ParticleSystemDemo(Scene* scene, const Vector3& g = { 0.0f, GRAVITY, 0.0f });
	void keyPress(unsigned char key) override;
private:
	void initForcesTest();
	void springTest();
	void rubberBandTest();
	void slinkyTest();
	void buoyancyTest();
	void anchoredSpringTest();
};

