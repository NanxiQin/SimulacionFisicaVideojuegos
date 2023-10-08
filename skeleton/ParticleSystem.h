#pragma once
#include "System.h"
#include "Particle.h"
#include "ParticleGenerator.h"
class ParticleSystem :public System {
public:
	// Creates a void system with a det. gravity
	ParticleSystem(Scene* scene, const Vector3& g = { 0.0f, -9.8f, 0.0f });
	~ParticleSystem();
	// Integrates the particles and checks for its lifetime, etc!
	void update(double t) override;
	// Method to generate a Firework with the appropiate type
	//void generateFirework(unsigned firework_type);

	// Gets a particle generator with name...
	//ParticleGenerator* getParticleGenerator(const std::string& n);
protected:
	list <ParticleGenerator*> particleGenerators;
	// These are the registred generators(for on demand set generation prob.to 0)
	//ParticleGenerator* _firework_generator;
	// This generator is only to shoot the firework!!
	Vector3 _gravity;
	//std::vector<Firework*> _firework_pool;// Fireworks to be used as models!
	//! This is used currently in the Fireworks to spread more Fireworks!
	//void onParticleDeath(Particle* p);
	//void createFireworkSystem()};

	inline bool isOutOfBounds(const Vector3& pos) const {
		return fabs(pos.x) > PARTICLE_BOUND_DISTANCE || fabs(pos.y) > PARTICLE_BOUND_DISTANCE || fabs(pos.z) > PARTICLE_BOUND_DISTANCE;
	}

} ;


