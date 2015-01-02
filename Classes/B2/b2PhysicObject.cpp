#include "b2PhysicObject.h"

#define PTM_RATIO 32.0
USING_NS_CC;
b2PhysicObject::b2PhysicObject(void)
{
}


b2PhysicObject::~b2PhysicObject(void)
{
}

void b2PhysicObject::update(float dt)
{
	if (_body && isVisible())
	{
		Node::setPosition(Vec2(_body->GetPosition().x * PTM_RATIO,_body->GetPosition().y * PTM_RATIO));
		Node::setRotation(CC_RADIANS_TO_DEGREES(-1 * _body->GetAngle()));
	}
}