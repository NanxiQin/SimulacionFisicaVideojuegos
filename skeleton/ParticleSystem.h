#pragma once
#include "System.h"
#include "Particle.h"
#include "Firework.h"
#include "ParticleGenerator.h"
#include "SimpleParticleGenerator.h".h"
#include "GaussianParticleGenerator.h".h".h"
class ParticleSystem :public System {
public:
	// Creates a void system with a det. gravity
	ParticleSystem(Scene* scene, const Vector3& g = { 0.0f, GRAVITY, 0.0f });
	~ParticleSystem();
	// Integrates the particles and checks for its lifetime, etc!
	void update(double t) override;
	void refresh();
	void keyPress(unsigned char key, const PxTransform& camera);

	// Method to generate a Firework with the appropiate type
	void generateFirework(bool randomColor, int maxGen);

	template <typename T>
	void initFirework(double prob, int nParticle);

	void addParticles(list<Particle*>particlesList);
protected:
	// These are the registred generators(for on demand set generation prob.to 0)
	list <ParticleGenerator*> particleGenerators;
	list <Particle*> particles;
	// This generator is only to shoot the firework!!
	ParticleGenerator* firework_generator;
	Vector3 gravity;

	//! This is used currently in the Fireworks to spread more Fireworks!
	void onParticleDeath(Particle* p);

	inline bool isOutOfBounds(const Vector3& pos) const {
		return fabs(pos.x) > PARTICLE_BOUND_DISTANCE || fabs(pos.y) > PARTICLE_BOUND_DISTANCE || fabs(pos.z) > PARTICLE_BOUND_DISTANCE;
	}

	template<class T>
	inline T* createGenerator(bool addTolist, GeneratorEffectType type = Default, Vector3 pos = { 0,0,0 }, Color color = COLOR_SIZE, DistributionProp distribution = generatorEffect[Default].distribution) {
		GeneratorEffectProperties g = generatorEffect[type];

		if (color != COLOR_SIZE)  g.model.color = colorRGB[color];
		if (pos != Vector3(0, 0, 0)) g.model.transform = PxTransform(pos);
		if (distribution != generatorEffect[Default].distribution) g.distribution = distribution;

		if (typeid(T) == typeid(GaussianParticleGenerator)) conversionUniformToGaussian(g.distribution);
		
		auto gen = new T(g);
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


