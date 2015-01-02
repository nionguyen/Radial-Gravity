#include "Ball.h"
#include "../Common/GameConfig.h"
#include "b2NodeManager.h"
#define PTM_RATIO 32.0
USING_NS_CC;
Ball::Ball(void)
{
	//oldPos = Vec2::ZERO;
}
#define G 67.0

Ball::~Ball(void)
{
}

Ball* Ball::create(cocos2d::Vec2 position,b2World* world,Node *node)
{
	Ball * sprite = new Ball();
	if (sprite) {
		sprite->initPhysic(position,world,node);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Ball::initPhysic(cocos2d::Vec2 position,b2World* world,Node *node)
{
	float radius = (15) / 2/ PTM_RATIO;
	_world = world;
	_type = kBall;
	this->setPosition(position);
	this->setContentSize(Size(radius * 2 * PTM_RATIO,radius *2 * PTM_RATIO));
	node->addChild(this,_type,kObject);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
	bodyDef.userData = this;
	bodyDef.fixedRotation = true;

	_body = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = radius;
	//b2PolygonShape circle;
	//circle.SetAsBox(15 / PTM_RATIO,30 /PTM_RATIO);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;    
	fixtureDef.density = 1.0f;
	//fixtureDef.friction = 1.0f;
	//fixtureDef.restitution = 0.5f;
	_body->CreateFixture(&fixtureDef); 
	
	b2Vec2 force = b2Vec2(CCRANDOM_MINUS1_1(),CCRANDOM_MINUS1_1());
	force = b2Vec2(0,-1);
	force.Normalize();
	float mag = 500 + 500 * CCRANDOM_0_1();
	mag = b2NodeManager::getInstance()->mag;
	CCLOG("data %f", mag);
	force = mag * _body->GetMass() * force;
	_body->ApplyForceToCenter(force,true);
}

void Ball::ClearGravitation()
{
	gravitationalForce.SetZero();
}

void Ball::AddGravitation(b2Vec2 distance, float mass)
{
	/*float diffDistance = (oldPos - this->getPosition()).getLengthSq();
	if(diffDistance > 300.0f)
	{
		auto point = Sprite::create("point.png");
		point->setScale(0.25f);
		point->setPosition(this->getPosition());
		this->getParent()->addChild(point,100);
		oldPos = this->getPosition();
	}*/
	float length = distance.LengthSquared();
	distance.Normalize();
	gravitationalForce += (G * mass * _body->GetMass()) / length * distance;
}

float Ball::GetGravityAngle()
{
	return (atan2(-gravitationalForce.x, gravitationalForce.y));
}

void Ball::Process()
{
	// Apply gravity
	_body->ApplyForce(gravitationalForce,_body->GetPosition(),true);
	_body->SetTransform(_body->GetWorldCenter(), atan2(-gravitationalForce.x, gravitationalForce.y));
}