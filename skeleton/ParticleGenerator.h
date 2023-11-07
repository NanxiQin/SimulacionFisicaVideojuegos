#pragma once
#include "RenderUtils.hpp"
#include "Entity.h"
#include "game_def.h"
#include <list>
#include "Particle.h"
#include <random> 
#include <iostream>
#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"
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
	//random
	uniform_real_distribution<double> probability;
	mt19937 mt;

	//std::string _name;

	ParticleForceRegistry* forceRegistry;

	ParticleGenerator(ParticleProperties modelParticle, Vector3 originOffset = { 0,0,0 }, double minLifeT = 0, double maxLifeT = 0, ParticleForceRegistry* forceRegistry = nullptr) :
		_model_particle(new Particle(modelParticle, false)), originOffset(originOffset), _origin(modelParticle.transform.p), _mean_velocity(modelParticle.vel), forceRegistry(forceRegistry),
		initMeanVelocity(modelParticle.vel), initOrigin(modelParticle.transform.p), minLifeTime(minLifeT), maxLifeTime(maxLifeT)
	{
		if (!maxLifeTime)maxLifeTime = modelParticle.lifeTime;
		mt = mt19937{ random_device()() };
		srand((unsigned)time(0));

	};
public:

	~ParticleGenerator() {
		delete _model_particle; //se asegura que no se ha borrado anteriormente, porque en al añadirlo a la lista en la generación siempre se crea uno nuevo no usado
		forceRegistry->deleteParticleGenRegistry(this); //deregistrarse
	}
	void addParticleRegistry(Particle* p) {
		for (auto fg : forceRegistry->ParticleGenMap()[this]) { //recorre su lista correspondiente de fuerzas
			forceRegistry->addParticleRegistry(fg, p);
		}
	}
	void addForceRegistry(ParticleForceRegistry* fr) { forceRegistry = fr; }
	void addForceGenerators(list<ForceGenerator*> fg) {

		for (auto f : fg) forceRegistry->addParticleGenRegistry(f, this);

	}
	void deleteForceGenerator(ForceGenerator* fg) {
		forceRegistry->deleteForceRegistryFromGen(fg, this);

	}
	virtual list<Particle*> generateParticles() = 0;
	virtual Vector3 generateNewDistribution() = 0;

	inline list<Particle*> generalParticleGeneration() {
		list<Particle*> list;
		if (!hasSurpassParticleMaxNum(_model_particle->getType())) //generar según prob
			for (int i = 0; i < _n_particles; ++i) {
				if (checkGenerationProb()) { //comproobar para cada particula si hay que generar
					//prop
					_model_particle->getPos() = generateRandomPos(_origin);
					_model_particle->getVel() = generateNewDistribution() * (_mean_velocity);
					setRandomLifeTime();

					_model_particle->registerRender(); //se renderiza si anteriormente no se ha registrado

					addParticleRegistry(_model_particle);

					list.push_back(_model_particle);

					setParticle(_model_particle); //generar una copia del modelo ya que se ha usado para la lista
				}
			}
		return list;
	}


	inline bool hasSurpassParticleMaxNum(ParticleType type) {
		return particleNum[type] > particleMaxNum[type];
	}

	inline bool checkGenerationProb() {
		double n = (uniform_real_distribution<double>(0, 1))(mt);
		return(n < _generation_prob);
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
		return colorRGB[rand() % Brown];
	}
	inline void setColor(Vector4 c) {
		_model_particle->setColor(c);
	}
	inline void setRandomColor() {
		_model_particle->setColor(getRandomColor());
	}
	inline void setRandomLifeTime() { //lifetime de la particula modelo como max
		_model_particle->setLifeTime(uniform_real_distribution<float>(minLifeTime, maxLifeTime)(mt));
	}

	inline void resetElapsedTime() {
		_model_particle->resetElapsedTime();

	}
	inline Vector3 generateRandomPos(Vector3 pos) {
		return {
		(uniform_real_distribution<float>(pos.x, pos.x + originOffset.x))(mt),
		(uniform_real_distribution<float>(pos.y, pos.y + originOffset.y))(mt),
		(uniform_real_distribution<float>(pos.z, pos.z + originOffset.z))(mt) };
	}

	////! @brief --> sets the particle, including its type, lifetime and mean positions and velocities
	inline void setParticle(Particle* p, bool modify_pos = false, bool modify_vel = false) {
		if (_model_particle != p)  delete _model_particle; //para no borrar a sí mismo
		_model_particle = p->clone(false); //para no renderizar
		if (modify_pos) {
			_origin = p->getPos();
		}
		if (modify_vel) {
			_mean_velocity = p->getVel();
		}

	}

	inline void setNParticles(int n_p) { _n_particles = n_p; }
	inline void setGenProb(double prob) { _generation_prob = prob; }
	virtual void keyPress(unsigned char key) {};

};


