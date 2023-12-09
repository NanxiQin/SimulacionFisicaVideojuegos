#pragma once
#include "System.h"
#include "ShooterManager.h"
#include "Particle.h"
#include "Firework.h"
#include "SimpleParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindsForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "AnchoredSpringForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "RubberBandForceGenerator.h"


class ParticleSystem :public System {
public:
	// Creates a void system with a det. gravity
	ParticleSystem(Scene* scene, const Vector3& g = { 0.0f, GRAVITY, 0.0f });
	virtual ~ParticleSystem();
	// Integrates the particles and checks for its lifetime, etc!
	void update(double t) override;
	virtual void refresh();
	virtual void keyPress(unsigned char key) {};

	virtual void addParticles(list<Particle*>particlesList);
	virtual void addGravity(Particle* particle);
	virtual void addFloating(Particle* particle);
protected:
	bool hasGravity;
	Vector3 gravity;

	ShooterManager* shooter;

	// These are the registred generators(for on demand set generation prob.to 0)
	list <ParticleGenerator*> particleGenerators;
	list <Particle*> particles;

	//Force
	ParticleForceRegistry* forceRegistry;

	list <ForceGenerator*> forceGenerators;
	GravityForceGenerator* gravityForce;
	GravityForceGenerator* floatingForce;

	// This generator is only to shoot the firework
	vector< ParticleGenerator*>firework_generators;


	void cleanSystem();
	void resetSystem();
	// Method to generate a Firework with the appropiate type
	void generateFirework(bool randomColor, int maxGen, int gen);

	template <typename T>
	void initFirework(double prob, int nParticle);
	void createFireworkGenerators();
	
	template<class T, typename ...Ts>
	inline T* createForceGenerators(Ts&&...args) {
		T* fg = new T(forward<Ts>(args)...);
		forceGenerators.push_back(fg);
		return fg;
	}

	void addForcetoAllParticles(list <ForceGenerator*> fg);

	void deleteAllParticleGenerators();
	void deleteParticleGenerator(ParticleGenerator* gen);
	void deleteForceGenerator(ForceGenerator* fg);
	void addForcetoAllParticlegenerators(list <ForceGenerator*> fg);

	void deregisterForceGenerator(ForceGenerator* fg);
	void deregisterForceGeneratorFromGen(ForceGenerator* fg, ParticleGenerator* gen);

	//! This is used currently in the Fireworks to spread more Fireworks!
	void onParticleDeath(Particle* p);


	inline bool isOutOfBounds(const Vector3& pos) const {
		return fabs(pos.x) > PARTICLE_BOUND_DISTANCE || fabs(pos.y) > PARTICLE_BOUND_DISTANCE || fabs(pos.z) > PARTICLE_BOUND_DISTANCE;
	}

	template<class T>
	inline T* createGenerator(bool addTolist, GeneratorEffectType type = DefaultEffect, Vector3 pos = { 0,0,0 }, Color color = COLOR_SIZE, DistributionProp distribution = generatorEffect[DefaultEffect].distribution) {
		GeneratorEffectProperties g = generatorEffect[type];
		if (color != COLOR_SIZE)  g.model.color = colorRGB[color];
		if (pos != Vector3(0, 0, 0)) g.model.transform = PxTransform(pos);
		if (distribution != generatorEffect[DefaultEffect].distribution) g.distribution = distribution;

		if (typeid(T) == typeid(GaussianParticleGenerator)) conversionUniformToGaussian(g.distribution);
		
		auto gen = new T(g);
		gen->addForceRegistry(forceRegistry);
		if (addTolist)
			particleGenerators.push_back(gen);
		return gen;
	}
	void conversionUniformToGaussian(DistributionProp& d) {
		d.x.first = (d.x.first + d.x.second) / 2; //conversión de min a media
		d.x.second = abs(d.x.second - d.x.first);//conversión de max a varianza
		d.y.first = (d.y.first + d.y.second) / 2;
		d.y.second = abs(d.y.second - d.y.first);
		d.z.first = (d.z.first + d.z.second) / 2;
		d.z.second = abs(d.z.second - d.z.first);
	}

	void debugNumParticle();
};


