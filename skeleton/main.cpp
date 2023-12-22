#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "DemoScene.h"
#include "GameScene.h"
#include <iostream>

#include <windows.h>

std::string display_text = "Game";
std::string displayTexts[2] = { "1-3 Fireworks | 4 UniformGen | 5 GuassianGen | 6 HoseEffect | 7 FogEffect | 8 RainEffect | 9 MilkyEffect" ,"e wind | r tornado | t explosion | y spring | u anchoredSpring | i rubberBand | o slinky | p buoyancy | z deleteLastGen | x checkGravity | c deleteLastForce" };


using namespace physx;
using namespace std;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;
Scene* sceneMng;



// Define collision groups and masks
const PxU32 CollisionGroupWall = 1 << 0;      // Collision group for the wall
const PxU32 CollisionGroupSphereA = 1 << 1;   // Collision group for sphere A
const PxU32 CollisionGroupOther = 1 << 2;     // Collision group for other objects


// Create collision filtering shader callback
PxFilterFlags CustomFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize) {

	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// Collision filtering logic
	if ((filterData0.word0 == CollisionGroupWall && filterData1.word0 == CollisionGroupSphereA) ||
		(filterData0.word0 == CollisionGroupSphereA && filterData1.word0 == CollisionGroupWall)||
		(filterData0.word0 == CollisionGroupOther && filterData1.word0 == CollisionGroupOther) ||
		(filterData0.word0 == CollisionGroupOther && filterData1.word0 == CollisionGroupSphereA) ||
		(filterData0.word0 == CollisionGroupSphereA && filterData1.word0 == CollisionGroupOther)) {
		// Collide only if between wall and sphere A
		pairFlags = PxPairFlag::eSOLVE_CONTACT |physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
			| physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
			| physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS
			| physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;  // Define collision behavior
		return physx::PxFilterFlag::eDEFAULT; // Return flags indicating collision is allowed
	}

	// For other combinations, disable collision
	pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
	return physx::PxFilterFlag::eKILL;

}


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, GRAVITY, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	//sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.filterShader = CustomFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	sceneMng = new GameScene();

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{

	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	sceneMng->update(t);


}

// Function to clean data/memory
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	//delete objects---------------------------------
	delete sceneMng;

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	sceneMng->keyPress(key);
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case ' ':
	{
		//shoot();

		break;
	}
	default:
		break;
	}
}

void keyRelease(unsigned char key)
{
	sceneMng->keyRelease(key);
}

void handleMouse(int button, int state, int x, int y)
{
	sceneMng->handleMouse(button, state, x, y);
}

void handleMotion(int x, int y)
{
	sceneMng->handleMotion(x, y);
}


void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	//PX_UNUSED(actor1);
	//PX_UNUSED(actor2);
	sceneMng->onCollision(actor1, actor2);
}


int main(int, const char* const*)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}