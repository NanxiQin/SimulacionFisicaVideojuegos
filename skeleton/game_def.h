#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"
using namespace physx;
namespace game_def {
	enum Color { Red, Orange, Yellow, Green, Blue, Purple, Pink, Brown, Black, White, Grey, COLOR_SIZE };
	static Vector4 colorRGB[COLOR_SIZE]{
		{1,0,0,1}, //Red
		{0.7,0.3,0,1}, //Orange
		{0.5,0.4,0,1}, //Yellow
		{0.3,0.4,0,1}, //Green
		{0.3,0.3,0.7,1}, //Blue
		{0.5,0.2,0.5,1}, //Purple
		{0.6, 0.3, 0.3, 1}, //Pink
		{1,1,0.5,1}, //Brown
		{0.1,0.1,0.1,1}, //Black
		{1,1,1,1},//White
		{0.5,0.5,0.5,1}//Grey
	};

	enum ParticleType { PISTOL, ARTILLERY, FIREBALL, LASER,NONE };
	enum KEY {
		shoot_Pistol = 'v',
		shoot_Artillery = 'b',
		shoot_Fireball = 'n',
		shoot_Laser = 'm'
	};

	struct ParticleProperties {
		PxTransform transform;
		Vector3 vel; //m/s
		Vector3 acceleration;
		double damping;
		double mass; //kg
		Vector4 color;
		double lifeTime;
		double elapsedTime = 0;
		ParticleType type = NONE;
	};

	struct ProjectileInitProperties {
		double velocity;
		double vertical_v;
		Vector3 acceleration;
		double damping;
		double mass; //kg
		Color color;
	};



	static ProjectileInitProperties projectileProperties[4]{
		{35,0,{0, -1, 0},0.99,0.5,Purple},
		{40,30,{0, -20, 0},0.99,5,Black},
		{10,0,{0, 4, 0},0.9,2,Orange}, //floats
		{100,0,{0,0, 0},0.99,0.1,Blue} //No gravity
	};

	const Vector3 UNIFORM_ORIGIN = { -40,0,0 };
	const Vector3 NORMAL_ORIGIN = { 40,0,0 };
	const Vector3 UNIFORM_VELOCITY = { 5,5,5 };
	const Vector3 NORMAL_VELOCITY = { 5,5,5 };

	const double

		PROJECTILE_LIFETIME = 5.0,//in seg

		SHOOT_CD = 0.5, //in seg
		PARTICLE_BOUND_DISTANCE = 100.0, //in seg
		GRAVITY = -10.0,

		NORMAL_MEAN = 0, //media
		NORMAL_SIGMA = 5, //varianza
		NORMAL_LIFETIME = 5.0,//in seg

		UNIFORM_MIN = -5,
		UNIFORM_MAX = 5,
		UNIFORM_LIFETIME = 5.0,//in seg
		UNIFORM_ORIGIN_OFFSET =100,

		DEFAULT_DAMPING = 0.998;

		

}