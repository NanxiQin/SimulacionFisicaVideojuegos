#include "Player.h"
#include <iostream>
Player::Player(Vector3 pos, Color color, double radius, double mass, PxFilterData* filter) :
	DynamicRigidBody({ PxTransform(pos),{0,0,0},0.4,mass,radius,colorRGB[color],-1,0,NONE }, true, nullptr, GeometryType::eSPHERE, { 10,10,10 }, Vector3(-1), filter)
{
	//body->setWakeCounter(100000);

}


void Player::handleMotion(int x, int y)
{
	int dx =  originForce.x- x;
	int dy =  originForce.y-y;

	std::cout << dx << " " << dy<<endl;
	Vector3 f = {(float) dx ,0,(float)dy };

	//if (abs((getVel() - f).magnitude())- abs(getVel().magnitude()) >500 )
	//	setVel(Vector3(0));
	//f*= 10;
	body->addForce(f*200*prop.mass);
	//setVel(f);
	originForce.x = x;
	originForce.y = y;
}
void Player::update(double t)
{
	//std::cout << body->getLinearVelocity().z << " " << endl;
	if (body->getLinearVelocity().z < 20)
	body->addForce(Vector3(0,0,1) * prop.mass*650*t);
}
void Player::handleMouse(int button, int state, int x, int y)
{
	PX_UNUSED(state);
	PX_UNUSED(button);
	originForce.x = x;
	originForce.y = y;
}

