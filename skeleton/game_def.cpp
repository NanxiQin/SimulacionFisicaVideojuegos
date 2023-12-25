#include "game_def.h"
namespace game_def {
	extern int particleNum[PARTICLE_TYPE_SIZE] = {0,0,0,0,0,0};

	extern PxFilterData filterDataOther = { CollisionGroupOther,CollisionGroupOther,CollisionGroupOther,CollisionGroupOther };
	extern PxFilterData filterDataPlayer = { CollisionGroupPlayer,CollisionGroupPlayer,CollisionGroupPlayer,CollisionGroupPlayer };
	extern PxFilterData filterDataTrigger = { CollisionGroupTrigger,CollisionGroupTrigger,CollisionGroupTrigger,CollisionGroupTrigger };
	extern PxFilterData filterDataBackWall = { CollisionGroupBackWall,CollisionGroupBackWall,CollisionGroupBackWall,CollisionGroupBackWall};
	extern PxFilterData filterDataSpring = { CollisionGroupSpring,CollisionGroupSpring,CollisionGroupSpring,CollisionGroupSpring };
	extern PxFilterData filterDataGround = { CollisionGroupGround,CollisionGroupGround,CollisionGroupGround,CollisionGroupGround };
	
}