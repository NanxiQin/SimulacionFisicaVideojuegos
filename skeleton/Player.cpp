#include "Player.h"
#include <iostream>
#include "GameScene.h"
Player::Player(GameScene* scene, Vector3 pos, Vector3 metaPos, PxMaterial* mat, Color color, double radius, double mass, PxFilterData filter) :
	DynamicRigidBody({ PxTransform(pos),{0,0,0},0.4,mass,radius,colorRGB[color],-1,0,NONE }, true, mat, GeometryType::eSPHERE, Vector3(0), Vector3(-1), filter),
	scene(scene), keyPressed(' '),metaPos(metaPos), originForce({0,0}),active(false) {}


void Player::handleMotion(int x, int y)
{
	if (!active)return;
	int dx = originForce.x - x;
	int dy = originForce.y - y;

	Vector3 f = { (float)dx ,0,(float)dy };
	
	if (body->getLinearVelocity().magnitude() < 300)
		body->addForce(f * 300 * prop.mass);

	originForce.x = x;
	originForce.y = y;
}
void Player::update(double t)
{
	if (!active)return;
	DynamicRigidBody::update(t);

	//Manage player movement if a key is pressed
	Vector3 dir = Vector3(0);
	switch (keyPressed)
	{
	case 'w':dir = Vector3(0, 0, 1); break;
	case 'a':dir = Vector3(1, 0, 0); break;
	case 's':dir = Vector3(0, 0, -1); break;
	case 'd':dir = Vector3(-1, 0, 0); break;
	}
	body->addForce(dir * 1020 * prop.mass);

	//Player reaches the goal
	if (getPos().z > metaPos.z) {
		scene->onPlayerWin();
		body->clearForce();
		body->setLinearVelocity(Vector3(0,0,10));
		body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		active = false;
	}
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

	Vector4 c = colorRGB[COLOR2];
	//Vector4 c = colorRGB[Purple];
	RigidBody* rb;
	if (actor1 == body) {
		//collides with obstacle
		if (scene->rigidBodyExists(actor2, rb) && rb->getColor() == c) alive = false;
			
	}
	else if (actor2 == body) {
		//collides with obstacle
		if (scene->rigidBodyExists(actor1, rb) && rb->getColor() == c) alive = false;
	}
}

void Player::handleMouse(int button, int state, int x, int y)
{
	if (!active)return;
	PX_UNUSED(state);
	PX_UNUSED(button);
	originForce.x = x;
	originForce.y = y;
}

void Player::die()
{
	if(active)
	scene->onPlayerLose();
	//DynamicRigidBody::die();

}