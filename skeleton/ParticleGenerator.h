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
	double _generation_prob = 1; // IF 1.0 --> always produces particles
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	Vector3 _origin, _mean_velocity;
	Vector3 initOrigin, initMeanVelocity;
	Vector3 originOffset;
	double minLifeTime;
	double maxLifeTime;
	ParticleProperties modelParticleProp;
	//random
	uniform_real_distribution<double> probability;
	mt19937 mt;

	std::string _name;

	ParticleGenerator(ParticleProperties modelParticle, Vector3 originOffset = { 0,0,0 },double minLifeT=0,double maxLifeT=0) :
		modelParticleProp(modelParticle), originOffset(originOffset), _origin(modelParticle.transform.p), _mean_velocity(modelParticle.vel), 
		initMeanVelocity(modelParticle.vel),initOrigin(modelParticle.transform.p),minLifeTime(minLifeT), maxLifeTime(maxLifeT)
	{
		if (!maxLifeTime)maxLifeTime = modelParticle.lifeTime;
		mt = mt19937{ random_device()() };
		srand((unsigned)time(0));

	};
public:
	~ParticleGenerator() {
		delete _model_particle; //se asegura que no se ha borrado anteriormente, porque en al añadirlo a la lista en la generación siempre se crea uno nuevo no usado
	}
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
	inline Vector3 getInitMeanVelocity() const {
		return initMeanVelocity;
	}
	inline Vector3 getInitOrigin() const {
		return initOrigin;
	}
	inline Vector4 getRandomColor() const {
		return colorRGB[rand() % Pink];
	}
	inline void setColor(Vector4 c) {
		_model_particle->setColor(c);
	}
	inline void setRandomColor() {
		//modelParticleProp.color = getRandomColor();
		_model_particle->setColor(getRandomColor());
	}
	inline void setRandomLifeTime() { //lifetime de la particula modelo como max
		_model_particle->setLifeTime(uniform_real_distribution<float>(minLifeTime, maxLifeTime)(mt));
	}

	inline void resetElapsedTime() {
		//modelParticleProp.elapsedTime =0;
		_model_particle->resetElapsedTime();
		
	}
	inline Vector3 generateRandomPos(Vector3 pos) {
		return {
		(uniform_real_distribution<float>(pos.x, pos.x + originOffset.x))(mt),
		(uniform_real_distribution<float>(pos.y, pos.y + originOffset.y))(mt),
		(uniform_real_distribution<float>(pos.z, pos.z + originOffset.z))(mt) };
	}

	////DUDA: A BORRAR
	////! @brief --> sets the particle, including its type, lifetime and mean positions and velocities
	inline void setParticle(Particle* p, bool modify_pos= false, bool modify_vel = false) {
		if(_model_particle!=p) delete _model_particle; //para no borrar a sí mismo
		_model_particle = p->clone(false); //para no renderizar
		if (modify_pos) {
			_origin = p->getPos();
		}
		if (modify_vel) {
			_mean_velocity = p->getVel();
		}
		
		//DUDA:hacerlo que no se registre en el constructor de la particula
		//_model_particle->getPos() = { -1000.0f, -1000.0f, -1000.0f };
	}

	/*inline void setNewParticleProp(ParticleProperties p, bool modify_pos_vel = true) {
		modelParticleProp = p;
		if (modify_pos_vel) {
			_origin = p.transform.p;
			_mean_velocity = p.vel;
		}
	}*/
	inline void setNParticles(int n_p) { _n_particles = n_p; }
	virtual void keyPress(unsigned char key) {};

};


