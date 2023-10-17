#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"
using namespace std;
using namespace physx;
namespace game_def {

	enum KEY {
		shoot_Pistol = 'v',
		shoot_Artillery = 'b',
		shoot_Fireball = 'n',
		shoot_Laser = 'm'
	};

#pragma region color
	enum Color { Red, Orange, Yellow, Green, Blue, Purple, Pink, Brown, Black, White, Grey, COLOR_SIZE };
	static Vector4 colorRGB[COLOR_SIZE]{
		{1,0,0,1}, //Red
		{0.7,0.3,0,1}, //Orange
		{0.7,0.6,0,3}, //Yellow
		{0.3,0.4,0,1}, //Green
		{0.5,0.5,0.9,1}, //Blue
		{0.5,0.2,0.5,1}, //Purple
		{0.6, 0.3, 0.3, 1}, //Pink
		{1,1,0.5,1}, //Brown
		{0.1,0.1,0.1,1}, //Black
		{1,1,1,1},//White
		{0.6,0.6,0.6,1}//Grey
	};
#pragma endregion

#pragma region particle

	enum ParticleType { NONE, PISTOL, ARTILLERY, FIREBALL, LASER, FIREWORK, PARTICLE_TYPE_SIZE };
	const double
		DEFAULT_DAMPING = 0.998,
		DEFAULT_LIFETIME = 5,
		DEFAULT_MASS = 1,

		PARTICLE_BOUND_DISTANCE = 500.0, //in seg
		GRAVITY = -10.0;


	struct ParticleProperties {
		PxTransform transform;
		Vector3 vel; //m/s
		Vector3 acceleration;
		double damping;
		double mass; //kg
		Vector4 color;
		double lifeTime;
		double elapsedTime;
		ParticleType type;
	};

	static int particleNum[PARTICLE_TYPE_SIZE]{ 0,0,0,0,0,0 };

	static ParticleProperties particleProperties[PARTICLE_TYPE_SIZE]{
		{PxTransform(0,0,0),{ 5,5,5 },{ 0,0,0 },DEFAULT_DAMPING,DEFAULT_MASS,colorRGB[Red],DEFAULT_LIFETIME,0,NONE},
		{PxTransform(0,0,0),{ 35,35,35 },{0,-1,0},0.99,0.5,colorRGB[Purple],DEFAULT_LIFETIME,0,PISTOL},
		{PxTransform(0,0,0),{ 40,70,40 },{0,-20,0},0.99,5,colorRGB[Black],DEFAULT_LIFETIME,0,ARTILLERY},
		{PxTransform(0,0,0),{ 10,10,10 },{0,4,0},0.9,2,colorRGB[Orange],DEFAULT_LIFETIME,0,FIREBALL},
		{PxTransform(0,0,0),{ 100,100,100 },{0,0,0},0.99,0.1,colorRGB[Blue],DEFAULT_LIFETIME,0,LASER},//No gravity
		{PxTransform(0,0,0),{ 0,40,0 },{0,GRAVITY,0},0.99,1,colorRGB[Red],DEFAULT_LIFETIME,0,FIREWORK},//No gravity
	
	};

#pragma endregion

#pragma region projectile
	const double
		SHOOT_CD = 0.5; //in seg
#pragma endregion


#pragma region particle generator
	enum GeneratorEffectType { Default, HoseEffect, FogEffect, MilkyWayEffect,FireworkEffect, GeneratorEffect_SIZE };

	struct DistributionProp {
		pair<double, double> x;
		pair<double, double> y;
		pair<double, double> z;
		bool operator==(const DistributionProp d) {
			return x == d.x && y == d.y && z == d.z;
		}
		bool operator!=(const DistributionProp d) {
			return !(*this == d);
		}
	};
	struct GeneratorEffectProperties {
		ParticleProperties model;
		Vector3 originOffset = { 0,0,0 };
		DistributionProp distribution;
	};

	static GeneratorEffectProperties generatorEffect[GeneratorEffect_SIZE]{
		{particleProperties[NONE],{ 10,10,10 }, {{-5,5},{-5,5},{-5,5}}},
		{{PxTransform(0,0,0),{5,30,1 },{0,-20,0}, DEFAULT_DAMPING,DEFAULT_MASS,colorRGB[Blue],DEFAULT_LIFETIME,0,NONE},{ 0,0,0 },{{5,10},{1.0,1.5},{-2,2}}},
		{{PxTransform(0,0,0),{ 0.5,0.5,0.5 },{0,GRAVITY,0}, DEFAULT_DAMPING,DEFAULT_MASS,colorRGB[Grey],DEFAULT_LIFETIME,0,NONE},{ 100,100,100 },{{-2,2},{-2,2},{-2,2}}},
		{{PxTransform(-40,0,0),{ 0.01,0.01,0.01 },{0,0,0}, DEFAULT_DAMPING,DEFAULT_MASS,colorRGB[Yellow],DEFAULT_LIFETIME,0,NONE},{ 200,0,50 },{{-2,2},{-2,2},{-2,2}}},
		{particleProperties[FIREWORK],{ 0,0,0 },{ {-5,5},{1,5},{-5,5}}},
	};

	const int FIREWORK_MAX_GEN=2;

#pragma endregion
}