#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"
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

	enum ProjectileType { PISTOL, ARTILLERY, FIREBALL, LASER, NONE };
	enum KEY {
		shoot_Pistol = 'v',
		shoot_Artillery = 'b',
		shoot_Fireball = 'n',
		shoot_Laser = 'm'
	};

	struct ParticleProperties {
		Vector3 trans;
		Vector3 vel; //m/s
		Vector3 acceleration;
		double damping;
		double mass; //kg
		Vector4 color;
		ProjectileType type = NONE;
	};

	struct ProjectileInitProperties {
		double velocity;
		double vertical_v;
		Vector3 acceleration;
		double damping;
		double mass; //kg
		Color color;
	};

	static ProjectileInitProperties particleProperties[NONE]{
		{35,0,{0, -1, 0},0.99,0.5,Purple},
		{40,30,{0, -20, 0},0.99,5,Black},
		{10,0,{0, 4, 0},0.9,2,Orange}, //floats
		{100,0,{0,0, 0},0.99,0.1,Blue} //No gravity
	};

	const double PROJECTILE_LIFETIME = 5; //in seg

	const double SHOOT_CD = 0.5; //in seg


	using hdlrId_type = unsigned int;
	enum hdlrId : hdlrId_type
	{
		_hdlr_EXAMPLE1,
		_LAST_HDLR_ID
	};
	constexpr hdlrId_type maxHdlrId = _LAST_HDLR_ID;

	using grpId_type = unsigned int;
	enum grpId : grpId_type {
		_grp_GENERAL,
		_grp_PROJECTILES,
		_grp_PARTICLES, //a cambiar
		_LAST_GRP_ID
	};
	constexpr grpId_type maxGroupId = _LAST_GRP_ID;

	using sysId_type = unsigned int;
	enum sysId : sysId_type {
		_sys_SHOOTER = 0,
		_sys_PARTICLE,
	
		// do not remove this
		_LAST_SYS_ID
	};
	constexpr sysId_type maxSystemId = _LAST_SYS_ID;
}