#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"
using namespace std;
using namespace physx;
namespace game_def {

	enum KEY {
		shoot_Pistol = 'f',
		shoot_Artillery = 'g',
		shoot_Fireball = 'h',
		shoot_Laser = 'j',

		add_Uniwind = 'e',
		add_Windwhirl = 'r',
		add_Explosion = 't',

		add_springTest = 'y',
		add_anchoredSpringTest = 'u',
		add_rubberbandTest = 'i',
		add_slinkyTest = 'o',
		add_buoyancyTest = 'p',

		shoot_Firework1 = '1',
		shoot_Firework2 = '2',
		shoot_Firework3 = '3',

		add_UniformGen = '4',
		add_GaussianGen = '5',

		add_HoseEffect = '6',
		add_FogEffect = '7',
		add_RainEffect = '8',
		add_MilkyEffect = '9',

		deleteLastParticleGen = 'z',
		checkGravity = 'x',
		deleteLastForceGen = 'c',

		increase = 'l',
		decrease = 'k',

		increaseMass = 'm',
		decreaseMass = 'n',

		increaseVolume = 'b',
		decreaseVolume = 'v'

	};

#pragma region color
	enum Color { Red, Orange, Yellow, Green, Blue, Purple, Pink, Brown, Black, White, Grey, TransparentBlue, TransparentPink, Transparent, COLOR_SIZE };
	static Vector4 colorRGB[COLOR_SIZE]{
		{0.5,0,0,1}, //Red
		{0.7,0.3,0,1}, //Orange
		{0.6,0.5,0,3}, //Yellow
		{0.3,0.4,0.1,1}, //Green
		{0.2,0.2,0.4,1}, //Blue
		{0.5,0.2,0.5,1}, //Purple
		{0.5, 0.2, 0.2, 1}, //Pink
		{1,1,0.5,1}, //Brown
		{0.1,0.1,0.1,1}, //Black
		{1,1,1,1},//White
		{0.4,0.4,0.4,1},//Grey
		{0.5,0.5,0.9,0.3},//TransparentBlue
		{0.6, 0.3, 0.3,0.5},//TransparentPink
		{0,0,0,0.1}//Transparent
	};
#pragma endregion

#pragma region particle

	enum ParticleType { NONE, PISTOL, ARTILLERY, FIREBALL, LASER, FIREWORK, STATIC, PARTICLE_TYPE_SIZE };
	const double
		DEFAULT_DAMPING = 0.998,
		DEFAULT_LIFETIME = 5,
		DEFAULT_MASS = 1,
		DEFAULT_RADIUS = 1,

		PARTICLE_BOUND_DISTANCE = 400.0,
		GRAVITY = -10.0,
		PI = 3.142857;
	const Vector3 FLOAT_FORCE = { 0,4,0 };

	struct ParticleProperties {
		PxTransform transform;
		Vector3 vel; //m/s
		double damping;
		double mass; //kg
		double radius;
		Vector4 color;
		double lifeTime;
		double elapsedTime;
		ParticleType type;
	};

	static ParticleProperties particleProperties[PARTICLE_TYPE_SIZE]{
		{PxTransform(0,0,0),{ 0,0,0 },DEFAULT_DAMPING,1,0.5,colorRGB[Red],DEFAULT_LIFETIME,0,NONE},
		{PxTransform(0,0,0),{ 300,300,300 },0.99,5,0.8,colorRGB[Purple],DEFAULT_LIFETIME,0,PISTOL},
		{PxTransform(0,0,0),{ 40,70,40 },0.99,5,5,colorRGB[Black],DEFAULT_LIFETIME,0,ARTILLERY},
		{PxTransform(0,0,0),{ 10,10,10 },0.9,2,2,colorRGB[Orange],DEFAULT_LIFETIME,0,FIREBALL},
		{PxTransform(0,0,0),{ 100,100,100 },0.99,0.1,0.1,colorRGB[Blue],DEFAULT_LIFETIME,0,LASER},//No gravity
		{PxTransform(0,0,0),{ 2,100,2 },0.99,0.5,0.5,colorRGB[White],0.5,0,FIREWORK},
		{PxTransform(0,0,0), { 0,0,0 }, 0, 0, 0, colorRGB[Grey], -1, 0, NONE }
	};

	extern int particleNum[PARTICLE_TYPE_SIZE];;
	static int particleMaxNum[PARTICLE_TYPE_SIZE]{ 1500,10,10,10,10,700,100 };


#pragma endregion

#pragma region projectile
	const double
		SHOOT_CD = 0.5; //in seg
#pragma endregion


#pragma region particle generator
	enum GeneratorEffectType { DefaultEffect, NeutralEffect, HoseEffect, FogEffect, RainEffect, MilkyWayEffect, FireworkEffect, GeneratorEffect_SIZE };

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
		{{PxTransform(0,0,0),{ 5,5,5 },DEFAULT_DAMPING,10,0.5,colorRGB[Red],DEFAULT_LIFETIME,0,NONE},{ 10,10,10 }, {{-5,5},{-5,5},{-5,5}},1,DEFAULT_LIFETIME},
		{{PxTransform(0,0,0),{0,0,0 }, DEFAULT_DAMPING,200,1,colorRGB[Red],DEFAULT_LIFETIME,0,NONE},{30,30,30}, {{-5,5},{-5,5},{-5,5}},15,20},
		{{PxTransform(0,0,0),{5,30,1 }, DEFAULT_DAMPING,3,0.3,colorRGB[Blue],DEFAULT_LIFETIME,0,NONE},{ 0,0,0 },{{5,10},{1.0,1.5},{-2,2}},DEFAULT_LIFETIME,10},
		{{PxTransform(0,0,0),{ 0.1,0.1,0.1 }, DEFAULT_DAMPING,0.5,0.1,colorRGB[Grey],7,0,NONE},{ 100,100,100 },{{-2,2},{-2,2},{-2,2}},DEFAULT_LIFETIME,DEFAULT_LIFETIME},
		{{PxTransform(0,0,0),{ 0.5,0,0.5 }, DEFAULT_DAMPING,1,0.2,colorRGB[Blue],DEFAULT_LIFETIME,0,NONE},{ 100,0,20 },{{-2,2},{0,0},{-2,2}},DEFAULT_LIFETIME,7},
		{{PxTransform(-40,0,0),{ 0.01,0.01,0.01 }, DEFAULT_DAMPING,0.5,0.1,colorRGB[Yellow],DEFAULT_LIFETIME,0,NONE},{ 200,0,50 },{{-2,2},{-2,2},{-2,2}},1,2},
		{{PxTransform(0,0,0),{ 5,20,5 },0.99,0.2,0.02,colorRGB[Blue],4,0,FIREWORK},{ 0,0,0 },{ {-3,3},{1,2},{-3,3}},1,1.5},
	};

	const int FIREWORK_MAX_GEN = 5;

#pragma endregion


#pragma region force_generator
	enum ForceGeneratorType { GravityForce, WindForce, WindWhirlForce, ExplosionForce, SpringForce, RubberBand, BuoyancyForce, ForceGenerator_SIZE };
#pragma endregion

#pragma region collision_filter
	// Define collision groups and masks
	const PxU32 CollisionGroupOther = 1 << 0;     // Collision group for other objects
	const PxU32 CollisionGroupBackWall = 1 << 1;  // Collision group for the wall
	const PxU32 CollisionGroupPlayer = 1 << 2;   // Collision group for player
	const PxU32 CollisionGroupTrigger = 1 << 4;   // Collision group for trigger
	const PxU32 CollisionGroupGround = 1 << 8;   // Collision group for ground
	const PxU32 CollisionGroupSpring = 1 << 16;   // Collision group for spring

	// Set collision groups and masks for other objects
	extern PxFilterData filterDataOther;

	// Set collision groups and masks for Player
	extern PxFilterData filterDataPlayer;

	// Set collision groups and masks for other TRIGGER
	extern PxFilterData filterDataTrigger;

	// Set collision groups and masks for the static back wall
	extern PxFilterData filterDataBackWall;

	// Set collision groups and masks for other ground
	extern PxFilterData filterDataGround;

	// Set collision groups and masks for other spring
	extern PxFilterData filterDataSpring;

#pragma endregion

#pragma region GameProperties
	const double PLAYER_INIT_OFFSET = 150;
	const double INIT_LENGTH = 150;
	const double FINAL_LENGTH = 100;
	const double ROAD_WIDTH = 150;
	const double COUNT = 3;

	const Color COLOR1 = Yellow;
	const Color COLOR2 = Blue;

	extern string display_text;
#pragma endregion
}