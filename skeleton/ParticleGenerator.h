#pragma once
#include "RenderUtils.hpp"
#include "Entity.h"
#include "game_def.h"
#include <list>
#include "Particle.h"
#include <random> 
using namespace std;
using namespace game_def;
class ParticleGenerator
{
protected:
	int _n_particles = 3; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	double _generation_prob = 1.0; // IF 1.0 --> always produces particles
	//DUDA: puede que no se necesite
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	Vector3 _origin, _mean_velocity;
	Vector3 originOffset;

	ParticleProperties modelParticleProp;
	//random
	uniform_real_distribution<double> probability;
	mt19937 mt;

	std::string _name;

	ParticleGenerator(ParticleProperties modelParticle, Vector3 originOffset = { 0,0,0 }):
		modelParticleProp(modelParticle), originOffset(originOffset), _origin(modelParticle.transform.p), _mean_velocity(modelParticle.vel)
	{
		mt = mt19937{ random_device()() };
	};
public:

	virtual list<Particle*> generateParticles() = 0;
	inline bool checkGenerationProb() {
		return (uniform_real_distribution<double>(0, 1 - _generation_prob))(mt) == 0;
	}
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_velocity = v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_velocity;
	}
	inline void setMeanDuration(double new_duration) {
		_model_particle->setLifeTime(new_duration);
	}

	//DUDA: A BORRAR
	//! @brief --> sets the particle, including its type, lifetime and mean positions and velocities
	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		delete _model_particle;
		_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->getPos();
			_mean_velocity = p->getVel();
		}
		_model_particle->getPos() = { -1000.0f, -1000.0f, -1000.0f };
	}

	inline void setNewPartcleProp(ParticleProperties p, bool modify_pos_vel = true) {
		modelParticleProp = p;
		if (modify_pos_vel) {
			_origin = p.transform.p;
			_mean_velocity = p.vel;
		}
	}
	inline void setNParticles(int n_p) { _n_particles = n_p; }
	virtual void keyPress(unsigned char key) {};

};


