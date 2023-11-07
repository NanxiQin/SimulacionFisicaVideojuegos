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
		shoot_Laser = 'm',

		add_Uniwind='z',
		add_Windwhirl ='x',
		add_Explosion='c',

		shoot_Firework1 = '1',
		shoot_Firework2 = '2',
		shoot_Firework3 = '3',
		
		add_UniformGen = '4',
		add_GaussianGen = '5',

		add_HoseEffect = '6',
		add_FogEffect = '7',
		add_RainEffect = '8',
		add_MilkyEffect = '9'


	};

#pragma region color
	enum Color { Red, Orange, Yellow, Green, Blue, Purple, Pink, Brown, Black, White, Grey, COLOR_SIZE };
	static Vector4 colorRGB[COLOR_SIZE]{
		{1,0,0,1}, //Red
		{0.7,0.3,0,1}, //Orange
		{0.7,0.6,0,3}, //Yellow
		{0.6,0.7,0,4}, //Green
		{0.5,0.5,0.9,1}, //Blue
		{0.5,0.2,0.5,1}, //Purple
		{0.6, 0.3, 0.3, 1}, //Pink
		{1,1,0.5,1}, //Brown
		{0.1,0.1,0.1,1}, //Black
		{1,1,1,1},//White
		{0.5,0.5,0.5,1}//Grey
	};
#pragma endregion

#pragma region particle

	enum ParticleType { NONE, PISTOL, ARTILLERY, FIREBALL, LASER, FIREWORK, PARTICLE_TYPE_SIZE };
	const double
		DEFAULT_DAMPING = 0.998,
		DEFAULT_LIFETIME = 5,
		DEFAULT_MASS = 1,
		DEFAULT_RADIUS= 1,

		PARTICLE_BOUND_DISTANCE = 500.0, //in seg
		GRAVITY = -10.0,
        PI = 3.142857;
	const Vector3 FLOAT_FORCE = { 0,4,0 };

	struct ParticleProperties {
		PxTransform transform;
		Vector3 vel; //m/s
		Vector3 acceleration;
		double damping;
		double mass; //kg
		double radius;
		Vector4 color;
		double lifeTime;
		double elapsedTime;
		ParticleType type;
	};

	extern int particleNum[PARTICLE_TYPE_SIZE];;
	static int particleMaxNum[PARTICLE_TYPE_SIZE]{ 800,10,10,10,10,700 };


	static ParticleProperties particleProperties[PARTICLE_TYPE_SIZE]{
		{PxTransform(0,0,0),{ 5,5,5 },{ 0,0,0 },DEFAULT_DAMPING,DEFAULT_MASS,DEFAULT_RADIUS,colorRGB[Red],DEFAULT_LIFETIME,0,NONE},
		{PxTransform(0,0,0),{ 200,200,200 },{0,-1,0},0.99,0.5,0.5,colorRGB[Purple],DEFAULT_LIFETIME,0,PISTOL},
		{PxTransform(0,0,0),{ 40,70,40 },{0,-20,0},0.99,5,5,colorRGB[Black],DEFAULT_LIFETIME,0,ARTILLERY},
		{PxTransform(0,0,0),{ 10,10,10 },{0,4,0},0.9,2,2,colorRGB[Orange],DEFAULT_LIFETIME,0,FIREBALL},
		{PxTransform(0,0,0),{ 100,100,100 },{0,0,0},0.99,0.1,0.1,colorRGB[Blue],DEFAULT_LIFETIME,0,LASER},//No gravity
		{PxTransform(0,0,0),{ 2,100,2 },{0,GRAVITY,0},0.99,0.5,0.5,colorRGB[White],2,0,FIREWORK},
	};

#pragma endregion

#pragma region projectile
	const double
		SHOOT_CD = 0.5; //in seg
#pragma endregion


#pragma region particle generator
	enum GeneratorEffectType { DefaultEffect,NeutralEffect, HoseEffect, FogEffect, RainEffect, MilkyWayEffect,FireworkEffect, GeneratorEffect_SIZE };

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
		double minLifeTime, maxLifeTime;
	};

	static GeneratorEffectProperties generatorEffect[GeneratorEffect_SIZE]{
		{particleProperties[NONE],{ 10,10,10 }, {{-5,5},{-5,5},{-5,5}},1,DEFAULT_LIFETIME},
		{{PxTransform(0,0,0),{0,0,0 },{0,0,0}, DEFAULT_DAMPING,1,1,colorRGB[Red],DEFAULT_LIFETIME,0,NONE},{10,10,10 }, {{-5,5},{-5,5},{-5,5}},5,10},
		{{PxTransform(0,0,0),{5,30,1 },{0,0,0}, DEFAULT_DAMPING,1,1,colorRGB[Blue],DEFAULT_LIFETIME,0,NONE},{ 0,0,0 },{{5,10},{1.0,1.5},{-2,2}},DEFAULT_LIFETIME,DEFAULT_LIFETIME},
		{{PxTransform(0,0,0),{ 0.1,0.1,0.1 },{0,0,0}, DEFAULT_DAMPING,0.2,0.2,colorRGB[Grey],7,0,NONE},{ 100,100,100 },{{-2,2},{-2,2},{-2,2}},DEFAULT_LIFETIME,DEFAULT_LIFETIME},
		{{PxTransform(0,0,0),{ 0.5,0,0.5 },{0,0,0}, DEFAULT_DAMPING,0.2,0.2,colorRGB[Blue],DEFAULT_LIFETIME,0,NONE},{ 100,0,20 },{{-2,2},{0,0},{-2,2}},DEFAULT_LIFETIME,7},
		{{PxTransform(-40,0,0),{ 0.01,0.01,0.01 },{0,0,0}, DEFAULT_DAMPING,0.1,0.1,colorRGB[Yellow],DEFAULT_LIFETIME,0,NONE},{ 200,0,50 },{{-2,2},{-2,2},{-2,2}},DEFAULT_LIFETIME,DEFAULT_LIFETIME},
		{{PxTransform(0,0,0),{ 5,20,5 },{0,0,0},0.99,0.2,0.2,colorRGB[Blue],4,0,FIREWORK},{ 0,0,0 },{ {-3,3},{1,2},{-3,3}},1,1.5},
	};

	const int FIREWORK_MAX_GEN=5;

#pragma endregion

	enum ForceGeneratorType { Gravity,ForceGenerator_SIZE };

}