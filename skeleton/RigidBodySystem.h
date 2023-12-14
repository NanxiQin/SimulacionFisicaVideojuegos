#pragma once
#include "ParticleSystem.h"
#include "DynamicRigidBody.h"
#include "StaticRigidBody.h"

class RigidBodySystem :public ParticleSystem
{
public:
	RigidBodySystem(Scene* scene, const Vector3& g = { 0.0f, GRAVITY, 0.0f });	
	void update(double t) override;
	void keyPress(unsigned char key) override;
	void resetSystem() override;
private:
	template<class T>
	inline T* createGenerator(bool addTolist,Particle* p, GeneratorEffectType type = DefaultEffect,Vector3 originOffset={-1,-1,-1}, double minLifeT=-2, double maxLifeT=-2, DistributionProp distribution = generatorEffect[DefaultEffect].distribution) {
		GeneratorEffectProperties g = generatorEffect[type];
		if (distribution != generatorEffect[DefaultEffect].distribution) g.distribution = distribution;
		if (originOffset != Vector3(-1, -1, -1)) g.originOffset = originOffset;
		if (minLifeT != -2) g.minLifeTime = minLifeT;
		if (maxLifeT != -2) g.maxLifeTime = maxLifeT;
		if (typeid(T) == typeid(GaussianParticleGenerator)) conversionUniformToGaussian(g.distribution);

		auto gen = new T(p,g.originOffset,g.distribution,g.minLifeTime,g.maxLifeTime);
		gen->addForceRegistry(forceRegistry);
		if (addTolist)
			particleGenerators.push_back(gen);
		return gen;
	}

	void rigidBodyDemo();
	pair<Particle*, Particle*> crosshair;
};

