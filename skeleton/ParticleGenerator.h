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
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	Vector3 _origin, _mean_velocity;
	//random
	mt19937 _mt;
	uniform_real_distribution<double> _u{ 0,1 };
	std::string _name;

public:
	
	virtual list<Particle*> generateParticles() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_velocity
			= v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_velocity;
	}
	inline void setMeanDuration(double new_duration) {
		_model_particle->setLifeTime(new_duration) ;
	}
	//! @brief --> sets the particle, including its type, lifetime and mean positions and velocities
	inline void setParticle(Particle* p, bool modify_pos_vel =true) {
		delete _model_particle;
		_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->getPos();
			_mean_velocity = p->getVel();
		}
		_model_particle->getPos() = { -1000.0f, -1000.0f, -1000.0f };
	}
	inline void setNParticles(int n_p) { _n_particles = n_p; }

};


