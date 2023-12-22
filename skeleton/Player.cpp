#include "Player.h"
#include <iostream>
#include "GameScene.h"
Player::Player(GameScene* scene, Vector3 pos, PxMaterial* mat, Color color, double radius, double mass, PxFilterData* filter) :
	DynamicRigidBody({ PxTransform(pos),{0,0,0},0.4,mass,radius,colorRGB[color],-1,0,NONE }, true, mat, GeometryType::eSPHERE, { 10,10,10 }, Vector3(-1), filter),
	scene(scene), keyPressed(' ')
{
	//body->setWakeCounter(100000);
}


void Player::handleMotion(int x, int y)
{
	int dx = originForce.x - x;
	int dy = originForce.y - y;

	//std::cout << dx << " " << dy<<endl;
	Vector3 f = { (float)dx ,0,(float)dy };

	//if (abs((getVel() - f).magnitude())- abs(getVel().magnitude()) >500 )
	//	setVel(Vector3(0));
	//f*= 10;
	if (body->getLinearVelocity().magnitude() < 800)
		body->addForce(f * 100 * prop.mass);
	//setVel(f);
	originForce.x = x;
	originForce.y = y;
}
void Player::update(double t)
{
	DynamicRigidBody::update(t);
	//std::cout << body->getLinearVelocity().z << " " << endl;
	/*if (body->getLinearVelocity().z < 20)
	body->addForce(Vector3(0,0,1) * prop.mass*650*t);*/

	Vector3 dir = Vector3(0);
	switch (keyPressed)
	{
	case 'w':dir = Vector3(0, 0, 1); break;
	case 'a':dir = Vector3(1, 0, 0); break;
	case 's':dir = Vector3(0, 0, -1); break;
	case 'd':dir = Vector3(-1, 0, 0); break;
	}
	body->addForce(dir * 1020 * prop.mass);
}
void Player::keyPress(unsigned char key)
{
	switch (key)
	{
	case 'w': case 'a':case 's':case 'd':keyPressed = key; break;
	}
}
void Player::keyRelease(unsigned char key)
{
	if (key == keyPressed)keyPressed = ' ';
}

void Player::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	Vector4 c = colorRGB[Purple];
	DynamicRigidBody* rb;
	if (actor1 == body) {
		if (scene->dynamicRigidBodyExists(actor2, rb) && rb->getColor() == c)
			alive = false;
	}
	else if (actor2 == body) {
		if (scene->dynamicRigidBodyExists(actor1, rb) && rb->getColor() == c)
			alive = false;
	}
}


void Player::die()
{
	DynamicRigidBody::die();
	scene->onPlayerDie();

}
void Player::handleMouse(int button, int state, int x, int y)
{
	PX_UNUSED(state);
	PX_UNUSED(button);
	originForce.x = x;
	originForce.y = y;
}

