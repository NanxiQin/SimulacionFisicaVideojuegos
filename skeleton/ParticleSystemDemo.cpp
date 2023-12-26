#include "ParticleSystemDemo.h"


ParticleSystemDemo::ParticleSystemDemo(Scene* scene, const Vector3& g):ParticleSystem(scene,g)
{
	createFireworkGenerators();
	//initForcesTest();
}

void ParticleSystemDemo::keyPress(unsigned char key)
{
	ForceGenerator* fg;
	switch (key)
	{
	case shoot_Firework1:
		generateFirework(false, 3, 0,GetCamera()->getEye(), GetCamera()->getDir());
		break;
	case shoot_Firework2:
		generateFirework(false, 5, 1, GetCamera()->getEye(), GetCamera()->getDir());
		break;
	case shoot_Firework3:
		generateFirework(true, 5, 2, GetCamera()->getEye(), GetCamera()->getDir());
		break;
	case add_UniformGen:
		createGenerator<SimpleParticleGenerator>(true, DefaultEffect, { -50,0,0 }, Pink)->addForceGenerators({ gravityForce });
		break;
	case add_GaussianGen:
		createGenerator<GaussianParticleGenerator>(true, DefaultEffect, { -50,0,0 }, Green)->addForceGenerators({ gravityForce });
		break;
	case add_HoseEffect:
		createGenerator<SimpleParticleGenerator>(true, HoseEffect)->addForceGenerators({ gravityForce });
		break;
	case add_FogEffect:
		createGenerator<GaussianParticleGenerator>(true, FogEffect);
		break;
	case add_RainEffect:
		createGenerator<SimpleParticleGenerator>(true, RainEffect)->addForceGenerators({ gravityForce });
		break;
	case add_MilkyEffect:
		createGenerator<SimpleParticleGenerator>(true, MilkyWayEffect);
		break;
	case add_Uniwind:
		//deleteForceGenerator(forceGenerators.back()); //OPCIONAL
		//addForcetoAllParticlegenerators({ createForceGenerators<WindForceGenerator>(0.3, Vector3(50, 20, 0)),gravityForce }); //FORMA1
		addForcetoAllParticles({ createForceGenerators<WindForceGenerator>(0.3, Vector3(5,2, 0)) }); //FORMA2
		break;
	case add_Windwhirl:
		//deleteForceGenerator(forceGenerators.back());
		//addForcetoAllParticlegenerators({ createForceGenerators<WhirlwindsForceGenerator>(0.01, 5,Vector3(0,0, 0),7),gravityForce });
		addForcetoAllParticles({ createForceGenerators<WhirlwindsForceGenerator>(0.01, 1,Vector3(0,-10,0),15) });
		break;
	case add_Explosion:
		//deleteForceGenerator(forceGenerators.back());
		//addForcetoAllParticlegenerators({ createForceGenerators<ExplosionForceGenerator>(Vector3(0,0,0), 200, 400000, 7),gravityForce });
		addForcetoAllParticles({ createForceGenerators<ExplosionForceGenerator>(Vector3(0,0,0), 200, 400000, 7) });
		break;
	case deleteLastParticleGen:
		cout << "deleteLastParticleGen" << endl;
		if (!particleGenerators.empty()) {
			deleteParticleGenerator(particleGenerators.back());
			particleGenerators.pop_back();
		}
		break;
	case checkGravity:
		(hasGravity = !hasGravity) ? addForcetoAllParticles({ gravityForce }) : deregisterForceGenerator(gravityForce);

		/*for (auto g : particleGenerators)
			deregisterForceGeneratorFromGen(gravityForce, g);*/

		break;
	case deleteLastForceGen:
		cout << "deleteLastForceGen" << endl;
		if (!forceGenerators.empty())
			deleteForceGenerator(forceGenerators.back());
		break;
	case add_springTest:
		springTest();
		break;
	case add_anchoredSpringTest:
		anchoredSpringTest();
		break;
	case add_rubberbandTest:
		rubberBandTest();
		break;
	case add_slinkyTest:
		slinkyTest();
		break;
	case add_buoyancyTest:
		buoyancyTest();
		break;
	case '0':
		resetSystem();;
		break;
	case increaseMass:
		for (auto p : particles)p->setMass(p->getMass() + 5);
		cout << "increasingMass" << endl;
		break;
	case decreaseMass:
		for (auto p : particles)p->setMass(p->getMass() * 0.75);
		cout << "decreaseMass" << endl;
		break;

	case increaseVolume:
		for (auto p : particles)p->setVolume(p->getScale() * 1.25);
		cout << "increasingVolume" << endl;
		break;
	case decreaseVolume:
		for (auto p : particles)p->setVolume(p->getScale() * 0.75);
		cout << "decreasingVolume" << endl;
		break;

	default:
		shooter->keyPress(key);
		for (auto fg : forceGenerators) fg->keyPress(key);
		break;
	}

}


void ParticleSystemDemo::initForcesTest()
{
	auto gen = createGenerator<SimpleParticleGenerator>(true, NeutralEffect, { 0,0,0 }, Blue);

	gen = createGenerator<SimpleParticleGenerator>(true, NeutralEffect, { 0,0,0 }, Grey);
	gen->setMass(50);

	gen = createGenerator<SimpleParticleGenerator>(true, NeutralEffect, { 0,0,0 }, Pink);
	gen->setRadius(0.5);
}

void ParticleSystemDemo::springTest()
{
	Particle* p1 = new Particle(particleProperties[NONE]);
	p1->setLifeTime(-1);
	p1->setPos({ -2,0,0 }) ;
	p1->setColor(colorRGB[Blue]);

	Particle* p2 = new Particle(particleProperties[NONE]);
	p2->setLifeTime(-1);
	p1->setPos({ 2,0,0 });
	p2->setColor(colorRGB[Pink]);

	forceRegistry->addParticleRegistry(createForceGenerators<SpringForceGenerator>(p2, 5, 10), p1);
	forceRegistry->addParticleRegistry(createForceGenerators<SpringForceGenerator>(p1, 5, 10), p2);
	addParticles({ p1,p2 });
}

void ParticleSystemDemo::rubberBandTest()
{
	Particle* p1 = new Particle(particleProperties[NONE]);
	p1->setLifeTime(-1);
	p1->setPos({ -2,0,0 });
	p1->setColor(colorRGB[Purple]);

	Particle* p2 = new Particle(particleProperties[NONE]);
	p2->setLifeTime(-1);
	p1->setPos({ 2,0,0 });
	p2->setColor(colorRGB[Orange]);

	forceRegistry->addParticleRegistry(createForceGenerators<RubberBandForceGenerator>(p2, 5, 10), p1); //longitud 10
	forceRegistry->addParticleRegistry(createForceGenerators<RubberBandForceGenerator>(p1, 5, 10), p2);
	addParticles({ p1,p2 });
}

void ParticleSystemDemo::anchoredSpringTest()
{
	Particle* p1 = new Particle(particleProperties[NONE]);
	p1->setLifeTime(-1);
	forceRegistry->addParticleRegistry(createForceGenerators<AnchoredSpringForceGenerator>(5, 10, Vector3(20, 0, 0)), p1);
	addParticles({ p1 });
}

void ParticleSystemDemo::slinkyTest()
{
	Particle* p1 = new Particle(particleProperties[NONE]);
	p1->setLifeTime(-1);
	p1->setPos({ 0,100,0 });
	p1->setColor(colorRGB[0]);
	p1->setRadius(1);
	p1->setMass(10);
	addParticles({ p1 });

	for (int i = 1; i < 6; ++i) {
		Particle* p2 = new Particle(particleProperties[NONE]);
		p2->setLifeTime(-1);
		p2->setPos({ 0,(float)(100 - i * 20),0 });
		p2->setColor(colorRGB[i % COLOR_SIZE]);
		p2->setRadius(1);
		p2->setMass(5);

		//forceRegistry->addParticleRegistry(createForceGenerators<RubberBandForceGenerator>(p2, 1, 15), p1);
		forceRegistry->addParticleRegistry(createForceGenerators<RubberBandForceGenerator>(p1, rand() % 5 + 1, rand() % 20 + 5), p2);

		addParticles({ p2 });

		p1 = p2;
	}

}

void ParticleSystemDemo::buoyancyTest()
{
	Particle* p1 = new Particle({ PxTransform(0,60,0), { 0,0,0 }, 0.8, 1, 0.5, colorRGB[Green], -1, 0, NONE }, true,PxGeometryType::eBOX,false,nullptr,{ 5,5,5 });
	Particle* p2 = new Particle({ PxTransform(0,60,50), { 0,0,0 }, DEFAULT_DAMPING, 1, 0.5, colorRGB[Red], -1, 0, NONE }, true, PxGeometryType::eBOX, false, nullptr, { 5,5,5 });
	Particle* p3 = new Particle({ PxTransform(50,60,0), { 0,0,0 }, 0.8, 1, 0.5, colorRGB[Yellow], -1, 0, NONE }, true, PxGeometryType::eBOX, false, nullptr,{ 5,15,5 });
	Particle* p4 = new Particle({ PxTransform(-50,60,0), { 0,0,0 }, 0.8, 1, 0.5, colorRGB[Purple], -1, 0, NONE }, true, PxGeometryType::eBOX, false, nullptr,{ 10,10,10 });

	addParticles({ p1,p2,p3,p4 });
	BuoyancyForceGenerator* f = createForceGenerators<BuoyancyForceGenerator>(Vector3(100, 20, 100));

	forceRegistry->addParticleRegistry(gravityForce, p1);
	forceRegistry->addParticleRegistry(gravityForce, p2);
	forceRegistry->addParticleRegistry(gravityForce, p3);
	forceRegistry->addParticleRegistry(gravityForce, p4);
	forceRegistry->addParticleRegistry(f, p1);
	forceRegistry->addParticleRegistry(f, p2);
	forceRegistry->addParticleRegistry(f, p3);
	forceRegistry->addParticleRegistry(f, p4);

}