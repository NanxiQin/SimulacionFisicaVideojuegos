#include "GameScene.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;


void GameScene::initGame()
{
	state = preparing;
	counter = 0;

	loadMap("./map.txt");


	rigidBodySys->setparticleBoundDistance(Vector3(1.5 * ROAD_WIDTH, 100, roadLength + 100));
	particleSys->setparticleBoundDistance(Vector3(1.5 * ROAD_WIDTH, 100, roadLength + 100));

	//Player................................................................................
	//Create Player
	rigidBodySys->addParticles({ player = new Player(this,{ 0,0,-PLAYER_INIT_OFFSET }, gPhysics->createMaterial(0.5f, 0.5f, 0.0f), Pink, 11, 10000, filterDataPlayer) });
	//Contrails
	constrail = particleSys->createGenerator<SimpleParticleGenerator>(true, DefaultEffect, { 0,0,0 }, White, { {-20,20},{-0.1,0.1},{-5,0} }, 1, 2);
	//Add wind force to player
	rigidBodySys->addForcetoParticle(rigidBodySys->createForceGenerators<WindForceGenerator>(0.3, Vector3(0, 0, 50), -1, Vector3(2 * ROAD_WIDTH, 100, roadLength)), player);

	//Adjust Camera's vision
	GetCamera()->setEye(player->getPos() + Vector3(0, 300, -100));
	GetCamera()->setDir(player->getPos() - GetCamera()->getEye());
	GetCamera()->setEye(GetCamera()->getEye() + Vector3(0, 0, 50));

	//Create Road
	//Ground
	StaticRigidBody* ground;

	rigidBodySys->addParticles({ ground = new StaticRigidBody(particleProperties[STATIC], gPhysics->createMaterial(0, 0, 0) ,filterDataGround, PxGeometryType::eBOX, { ROAD_WIDTH,1,(float)roadLength}) });
	ground->setPos({ 0,0,(float)(roadLength / 2.0 - INIT_LENGTH) });

	//Walls
	rigidBodySys->addParticles({ rightWall = new StaticRigidBody(particleProperties[STATIC], nullptr,filterDataOther, PxGeometryType::eBOX, { 10,20,(float)roadLength}) });
	rightWall->setPos({ ROAD_WIDTH,0,(float)(roadLength / 2.0 - INIT_LENGTH) });

	rigidBodySys->addParticles({ leftWall = new StaticRigidBody(particleProperties[STATIC], nullptr,filterDataOther, PxGeometryType::eBOX, { 10,20,(float)roadLength}) });
	leftWall->setPos({ -ROAD_WIDTH,0,(float)(roadLength / 2.0 - INIT_LENGTH) });

	rigidBodySys->addParticles({ backWall = new StaticRigidBody(particleProperties[STATIC], gPhysics->createMaterial(0.5f, 0.5f, 0.0f),filterDataBackWall, PxGeometryType::eBOX, { 155,20,10 }) });
	backWall->setPos({ 0,0,GetCamera()->getEye().z - 60 });




	//double offset = 2;
	//double wallOffset = 20;
	//double radius = 4;
	////for (int i = 0; i < 15; i++) { //row
	////	for (int j = 0; j < 15; j++) { //column
	////		rigidBodySys->addParticles({ new DynamicRigidBody({ PxTransform(-(j * (2 * radius + offset) - posWidth),0,-i * (2 * radius + offset)),{ 0,0,0 },0.8,2,radius,colorRGB[Yellow],-1,0,NONE }) });
	////	}
	////}
	//radius = 10;
	//double posWidth = (2 * radius + offset) * 10 - wallOffset;
	//DynamicRigidBody* aux;
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(j * (2 * radius + offset) - posWidth),0,-i * (2 * radius + offset)),{ 0,0,0 },0.8,2,radius,colorRGB[Purple],-1,0,NONE },true,nullptr,GeometryType::eSPHERE) });
	//		actorMap.insert({ aux->getActor(),aux });
	//	}
	//}


	//for (int i = 0; i < 8; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		rigidBodySys->addParticles({ new DynamicRigidBody({ PxTransform(j * 50 ,10,i * 50),{0,0,0},0.8,2,9,colorRGB[Blue],-1,0,NONE},true,nullptr,GeometryType::eBOX,{10,10,10}) });
	//	}
	//}

}
void GameScene::loadMap(const string& file)
{
	ifstream input;
	input.open(file);
	if (!input.is_open()) throw "can't open the file correctly";

	int rows, columns;
	//read rows and columns of the map
	input >> rows >> columns;

	//Errores al leer tamaño del mapa
	if (rows <= 0) throw "the map's row is out of the range";
	if (columns <= 0) throw "the map's column is out of the range";


	double offset = 2;
	double radius = 4;
	//double playerDistance=100;
	double wallOffset = 2;
	double cellWidth = 11;
	double posWidth, posLength;
	int color;

	roadWidth = ROAD_WIDTH;
	roadLength = cellWidth * rows + INIT_LENGTH + FINAL_LENGTH;

	DynamicRigidBody* aux;
	//posWidth = (2 * radius + offset) * columns - wallOffset;
	posWidth = cellWidth * columns / 2 - wallOffset;
	posLength = cellWidth * rows;
	//posLength = (2 * radius + offset) * rows;
	for (int row = 0; row < rows; row++) {
		string actualRow;
		input >> actualRow;
		int stringIndex = 0;
		int direction;
		for (int column = 0; column < columns; ++column, ++stringIndex) {
			switch (actualRow[stringIndex]) {
			case '-':break;
			case 'o':
				radius = 10;
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),0,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE }) });
				actorMap.insert({ aux->getActor(),aux });
				break;
			case '.':
				radius = 4;
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),0,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE }) });

				actorMap.insert({ aux->getActor(),aux });
				break;

			case 'b':
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),3,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE },true,nullptr,GeometryType::eBOX,{3,3,3}) });

				actorMap.insert({ aux->getActor(),aux });
				break;

			case 'v':
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),7,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE },true,nullptr,GeometryType::eBOX,{7,7,7}) });

				actorMap.insert({ aux->getActor(),aux });
				break;

			case 't':
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),7,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE },true,nullptr,GeometryType::eBOX,{30,7,7}) });

				actorMap.insert({ aux->getActor(),aux });
				break;
			case 'c':
				radius = 6;
				stringIndex++;
				char c = actualRow[stringIndex];
				color = atoi(&c);
				stringIndex++;
				direction = atoi(&actualRow[stringIndex]);
				direction == 1 ? direction = 1 : direction = -1;
				Vector3 anchoredPos = Vector3(-(column * (cellWidth)-posWidth + cellWidth / 2.0), 0, -(row * (cellWidth)-posLength + cellWidth / 2.0));
				Vector3 spherePos = anchoredPos + direction * Vector3(8 * cellWidth, 0, 0);

				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(spherePos),{ 0,0,0 },0,1,radius,colorRGB[color],-1,0,NONE },true, nullptr, GeometryType::eSPHERE, Vector3(0), Vector3(-1), filterDataSpring) });
				rigidBodySys->addForcetoParticle(rigidBodySys->createForceGenerators<AnchoredSpringForceGenerator>(10, 13 * cellWidth, anchoredPos), aux);
				aux->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
				actorMap.insert({ aux->getActor(),aux });
			}
		}
	}
	input.close();
}
GameScene::GameScene() :Scene()
{
	addSystem(particleSys = new ParticleSystem(this, Vector3{ 0,GRAVITY,0 }));
	addSystem(rigidBodySys = new RigidBodySystem(this, Vector3{ 0,GRAVITY,0 }));
	initGame();
}

void GameScene::handleMouse(int button, int state, int x, int y)
{
	Scene::handleMouse(button, state, x, y);

	//GetCamera()->handleMouse(button, state, x, y);
}

void GameScene::keyPress(unsigned char key)
{
	Scene::keyPress(key);
}

void GameScene::update(double t)
{
	switch (state)
	{
	case preparing:
		counter += t;
		if (counter > COUNT)
			state = playing;
		break;
	case pausing:
		break;
	case playing:
		constrail->setOrigin(player->getPos() + Vector3(-5, 0, -10));
		constrail->setMeanVelocity(-player->getVel().getNormalized());
		GetCamera()->setEye((GetCamera()->getEye() + Vector3(0, 0, 50) * t));
		backWall->setPos({ 0,0,GetCamera()->getEye().z - 60 });
		Scene::update(t);
		break;
	case end:
		Scene::update(t);
		break;
	default:
		break;
	}

}

void GameScene::handleMotion(int x, int y)
{
	Scene::handleMotion(x, y);

	//GetCamera()->handleMotion(x, y);
}

void GameScene::onPlayerDie()
{
	state = end;
	particleSys->deleteParticleGenerator(constrail);
}

bool GameScene::dynamicRigidBodyExists(PxActor* actor, DynamicRigidBody*& rb)
{
	rb = nullptr;
	auto it = actorMap.find(actor);
	if (it != actorMap.end()) {
		rb = (*it).second;
		return true;
	}
	else return false;
}

void GameScene::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	player->onCollision(actor1, actor2);
}

