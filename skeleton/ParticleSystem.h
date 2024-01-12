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
	virtual void keyPress(unsigned char key) ;
	virtual void keyRelease(unsigned char key) ;

	virtual void handleMotion(int x, int y);
	virtual void handleMouse(int button, int state, int x, int y);

	void setparticleBoundDistance(Vector3 d) { particleMaxBoundDistance= particleMinBoundDistance = d; };
	void setparticleBoundDistance(Vector3 min, Vector3 max) { particleMaxBoundDistance = max; particleMinBoundDistance = min;};

	virtual void addGravity(Particle* particle);
	virtual void addFloating(Particle* particle);

	void createFireworkGenerators();
	void generateFirework(bool randomColor, int maxGen, int gen,Vector3 pos,Vector3 dir);

	virtual void addParticles(list<Particle*>particlesList);
	void addForcetoAllParticles(list <ForceGenerator*> fg);
	void addForcetoParticle(ForceGenerator* fg, Particle* p);
	void addForcetoAllParticlegenerators(list <ForceGenerator*> fg);

	void deregisterForceGenerator(ForceGenerator* fg);
	void deregisterForceGeneratorFromGen(ForceGenerator* fg, ParticleGenerator* gen);

	void deleteAllParticleGenerators();
	void deleteParticleGenerator(ParticleGenerator* gen);
	void deleteForceGenerator(ForceGenerator* fg);

	
	template<class T>
	inline T* createGenerator(bool addTolist, GeneratorEffectType type = DefaultEffect, Vector3 pos = { 0,0,0 }, Color color = COLOR_SIZE, DistributionProp distribution = generatorEffect[DefaultEffect].distribution,double minLife=-2,double maxLife=-2) {
		GeneratorEffectProperties g = generatorEffect[type];
		if (color != COLOR_SIZE)  g.model.color = colorRGB[color];
		if (pos != Vector3(0, 0, 0)) g.model.transform = PxTransform(pos);
		if (distribution != generatorEffect[DefaultEffect].distribution) g.distribution = distribution;
		if (minLife !=-2) g.minLifeTime = minLife;
		if (maxLife !=-2) g.maxLifeTime = maxLife;

		if (typeid(T) == typeid(GaussianParticleGenerator)) conversionUniformToGaussian(g.distribution);

		auto gen = new T(g);
		gen->addForceRegistry(forceRegistry);
		if (addTolist)
			particleGenerators.push_back(gen);
		return gen;
	}	
	
	template<class T, typename ...Ts>
	inline T* createForceGenerators(Ts&&...args) {
		T* fg = new T(forward<Ts>(args)...);
		forceGenerators.push_back(fg);
		return fg;
	}

	

protected:
	bool hasGravity;
	Vector3 gravity;


	list <Particle*> particles;
	list <ParticleGenerator*> particleGenerators;
	list <ForceGenerator*> forceGenerators;

	ParticleForceRegistry* forceRegistry;

	GravityForceGenerator* gravityForce;
	GravityForceGenerator* floatingForce;

	ShooterManager* shooter;
	vector< ParticleGenerator*>firework_generators;

	Vector3 particleMaxBoundDistance;
	Vector3 particleMinBoundDistance;

	void cleanSystem();
	virtual void resetSystem();
	// Method to generate a Firework with the appropiate type

	template <typename T>
	void initFirework(double prob, int nParticle);

	//! This is used currently in the Fireworks to spread more Fireworks!
	void onParticleDeath(Particle* p);

	inline bool isOutOfBounds(const Vector3& pos) const {
		return
			pos.x > particleMaxBoundDistance.x || pos.x < particleMinBoundDistance.x||
			pos.y > particleMaxBoundDistance.y || pos.y < particleMinBoundDistance.y||
			pos.z > particleMaxBoundDistance.z || pos.z < particleMinBoundDistance.z;
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


