#include "GameScene.h"
extern PxPhysics* gPhysics;
extern PxScene* gScene;

GameScene::GameScene() :Scene()
{
	initGame();
}

void GameScene::initGame()
{
	state = preparing;
	counter = 0;

	addSystem(particleSys = new ParticleSystem(this, Vector3{ 0,GRAVITY,0 }));
	addSystem(rigidBodySys = new RigidBodySystem(this, Vector3{ 0,GRAVITY,0 }));
	addSystem(roadSys = new RigidBodySystem(this, Vector3{ 0,GRAVITY,0 }));

	loadMap("./map.txt");

	//Entities' DeadZone
	rigidBodySys->setparticleBoundDistance(Vector3(-1.5 * ROAD_WIDTH, -100, GetCamera()->getEye().z - 100), Vector3(1.5 * ROAD_WIDTH, 100, roadLength + 400));
	particleSys->setparticleBoundDistance(Vector3(-1.5 * ROAD_WIDTH, -100, GetCamera()->getEye().z - 100), Vector3(1.5 * ROAD_WIDTH, 100, roadLength + 400));
	roadSys->setparticleBoundDistance(Vector3(-1.5 * ROAD_WIDTH, -100, -roadLength-400), Vector3(1.5 * ROAD_WIDTH, 100, roadLength + 400));

	//Player................................................................................
	//Create Player
	rigidBodySys->addParticles({ player = new Player(this,{ 0,0,-PLAYER_INIT_OFFSET },metaPos, gPhysics->createMaterial(0.5f, 0.5f, 0.0f), COLOR1, 11, 10000, filterDataPlayer) });
	//Contrails
	constrail = particleSys->createGenerator<SimpleParticleGenerator>(true, DefaultEffect, { 0,0,0 }, White, { {-20,20},{-0.1,0.1},{-5,0} }, 1, 2);
	//Add windForce to Player
	rigidBodySys->addForcetoParticle(windForce = rigidBodySys->createForceGenerators<WindForceGenerator>(0.3, Vector3(0, 0, 64.5), -1, Vector3(2 * ROAD_WIDTH, 100, roadLength)), player);

	//Adjust Camera's vision
	GetCamera()->setEye(player->getPos() + Vector3(0, 300, -100));
	GetCamera()->setDir(player->getPos() - GetCamera()->getEye());
	GetCamera()->setEye(GetCamera()->getEye() + Vector3(0, 0, 100));

	//Create Road...........................................................................
	//Ground
	StaticRigidBody* ground;

	roadSys->addParticles({ ground = new StaticRigidBody(particleProperties[STATIC], gPhysics->createMaterial(0, 0, 0) ,filterDataGround, PxGeometryType::eBOX, { ROAD_WIDTH,1,(float)roadLength}) });
	ground->setPos({ 0,0,(float)(((roadLength / 2.0 - INIT_LENGTH))*2)});

	//Walls
	roadSys->addParticles({ leftWall = new StaticRigidBody(particleProperties[STATIC], nullptr,filterDataOther, PxGeometryType::eBOX, { 10,20,(float)roadLength}) });
	leftWall->setPos({ ROAD_WIDTH,0,(float)(roadLength / 2.0 - INIT_LENGTH) });
	leftWall->setColor(colorRGB[Black]);
	
	roadSys->addParticles({ rightWall = new StaticRigidBody(particleProperties[STATIC], nullptr,filterDataOther, PxGeometryType::eBOX, { 10,20,(float)roadLength}) });
	rightWall->setPos({ -ROAD_WIDTH,0,(float)(roadLength / 2.0 - INIT_LENGTH) });
	rightWall->setColor(colorRGB[Black]);

	roadSys->addParticles({ backWall = new StaticRigidBody(particleProperties[STATIC], gPhysics->createMaterial(0.5f, 0.5f, 0.0f),filterDataBackWall, PxGeometryType::eBOX, { 140,20,10 }) });
	backWall->setPos({ 0,0,GetCamera()->getEye().z - 60 });

}

void GameScene::loadMap(const string& file)
{
	ifstream input;
	input.open(file);
	if (!input.is_open()) throw "can't open the file correctly";

	int rows, columns;
	//read rows and columns of the map
	input >> rows >> columns;

	if (rows <= 0) throw "the map's row is out of the range";
	if (columns <= 0) throw "the map's column is out of the range";

	double offset = 2;
	double wallOffset = 3;
	double cellWidth = 11;
	int color;
	double radius;

	roadWidth = ROAD_WIDTH;
	roadLength = cellWidth * rows + INIT_LENGTH + FINAL_LENGTH;

	//CreateMapInitPos
	double posWidth, posLength;
	posWidth = cellWidth * columns / 2 - wallOffset;
	posLength = cellWidth * rows;

	DynamicRigidBody* aux;
	for (int row = 0; row < rows; row++) {
		string actualRow;
		input >> actualRow;
		int stringIndex = 0;
		int direction;
		for (int column = 0; column < columns; ++column, ++stringIndex) {
			switch (actualRow[stringIndex]) {
			case '-':break; //empty
			case 'o': //BigSphere
				radius = 10;
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				color == 0 ? color = COLOR1 : color = COLOR2;
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),0,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE }) });
				actorMap.insert({ aux->getActor(),aux });
				break;
			case '.'://SmallSphere
				radius = 4;
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				color == 0 ? color = COLOR1 : color = COLOR2;
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),0,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE }) });

				actorMap.insert({ aux->getActor(),aux });
				break;

			case 'b'://SmallCube
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				color == 0 ? color = COLOR1 : color = COLOR2;
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),3,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE },true,nullptr,GeometryType::eBOX,{3,3,3}) });

				actorMap.insert({ aux->getActor(),aux });
				break;

			case 'v'://BigCube
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				color == 0 ? color = COLOR1 : color = COLOR2;
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),7,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE },true,nullptr,GeometryType::eBOX,{7,7,7}) });

				actorMap.insert({ aux->getActor(),aux });
				break;

			case 't'://Cuboid
				stringIndex++;
				color = atoi(&actualRow[stringIndex]);
				color == 0 ? color = COLOR1 : color = COLOR2;
				rigidBodySys->addParticles({ aux = new DynamicRigidBody({ PxTransform(-(column * (cellWidth)-posWidth + cellWidth / 2.0),7,-(row * (cellWidth)-posLength + cellWidth / 2.0)),{ 0,0,0 },0.8,2,radius,colorRGB[color],-1,0,NONE },true,nullptr,GeometryType::eBOX,{30,7,7}) });

				actorMap.insert({ aux->getActor(),aux });
				break;
			case 'c'://Spring
				radius = 6;
				stringIndex++;
				char c = actualRow[stringIndex];
				color = atoi(&c);
				color == 0 ? color = COLOR1 : color = COLOR2;
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

	//Goal
	vector<int>bw({ Black,White });
	cellWidth = 10;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 30; ++j) {
			int color = bw[(i % 2 + j % 2) % 2]; //aternatively changing black and white color
			particleSys->addParticles({ new Particle({ PxTransform(-(j * (cellWidth)-(ROAD_WIDTH)+cellWidth / 2.0),4,-(i * (cellWidth)-posLength - 100 + cellWidth / 2.0)),{ 0,0,0 },0.8,2,1,colorRGB[color],-1,0,NONE },true,GeometryType::eBOX,true,nullptr,{5,0.5,5}) });

		}
	}
	metaPos = { 0, 7,(float)posLength+100 };
	roadSys->addParticles({ new StaticRigidBody({ PxTransform(0,7,posLength + 200),{ 0,0,0 },0.8,2,radius,colorRGB[Black],-1,0,NONE },gPhysics->createMaterial(0.5f, 0.5f, 0.0f),filterDataTrigger, PxGeometryType::eBOX, { (float)roadWidth,100,50})});
}

void GameScene::update(double t)
{
	switch (state)
	{
	case preparing:
		counter += t;
		if (counter > COUNT)
			state = pausing;
		break;
	case pausing:
		break;
	case playing:
		GetCamera()->setEye((GetCamera()->getEye() + Vector3(0, 0, 50) * t));
		onPlaying();
		Scene::update(t);
		break;
	case win:shootFireworks(); Scene::update(t); break;
	case lose:Scene::update(t);break;
	default:
		break;
	}

}

void GameScene::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	switch (state)
	{
	case playing:player->onCollision(actor1, actor2);break;
	}
}

void GameScene::handleMouse(int button, int state, int x, int y)
{
	
	switch (state)
	{

	case preparing:case pausing:case playing:Scene::handleMouse(button, state, x, y);break;
	}

	//GetCamera()->handleMouse(button, state, x, y);
}

void GameScene::handleMotion(int x, int y)
{
	
	switch (state)
	{
	case preparing:case pausing:case playing:Scene::handleMotion(x, y);break;
	}
	//GetCamera()->handleMotion(x, y);
}

void GameScene::keyPress(unsigned char key)
{
	switch (state)
	{
	case preparing:break;
	case pausing:if (key == ' ')state = playing;player->setActive(); break;
	case playing:Scene::keyPress(key);break;
	case win:case lose: if (key == 'r')onRestart(); break;
	}
}

void GameScene::onPlayerLose()
{
	state = lose;
	particleSys->deleteParticleGenerator(constrail);
	rigidBodySys->addForcetoAllParticles({ rigidBodySys->createForceGenerators<ExplosionForceGenerator>(player->getPos(), 200, 40000, 0.5)});
}

void GameScene::onPlayerWin()
{
	state = win;
	rigidBodySys->deregisterForceGenerator(windForce);
	particleSys->deleteParticleGenerator(constrail);
	particleSys->createFireworkGenerators();
}

void GameScene::onRestart()
{
	systems.clear();
	delete particleSys;
	delete rigidBodySys;
	delete roadSys;
	actorMap.clear();
	initGame();
}

void GameScene::onPlaying()
{
	//move constrail
	constrail->setOrigin(player->getPos() + Vector3(-5, 0, -10));
	constrail->setMeanVelocity(-player->getVel().getNormalized());
	//move backwall
	backWall->setPos({ 0,0,GetCamera()->getEye().z - 60 });
	//update DeadZone
	rigidBodySys->setparticleBoundDistance(Vector3(-1.5 * ROAD_WIDTH, -100, GetCamera()->getEye().z - 100), Vector3(1.5 * ROAD_WIDTH, 100, roadLength + 400));
	particleSys->setparticleBoundDistance(Vector3(-1.5 * ROAD_WIDTH, -500, GetCamera()->getEye().z - 100), Vector3(1.5 * ROAD_WIDTH, 400, roadLength + 600));
}

void GameScene::shootFireworks()
{
	particleSys->generateFirework(true, 3, 2, Vector3(-100, -0, GetCamera()->getEye().z + 100), Vector3(1, 1, 0));
	particleSys->generateFirework(true, 3, 2, Vector3(0, -0, GetCamera()->getEye().z + 100), Vector3(0, 1, 0));
	particleSys->generateFirework(true, 3, 2, Vector3(100, -0, GetCamera()->getEye().z + 100), Vector3(-1, 1, 0));
}

bool GameScene::rigidBodyExists(PxActor* actor, RigidBody*& rb)
{
	rb = nullptr;
	auto it = actorMap.find(actor);
	if (it != actorMap.end()) {
		rb = (*it).second;
		return true;
	}
	else return false;
}


