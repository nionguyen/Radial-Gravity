#include "Planet.h"
#include "../Common/GameConfig.h"
#include "b2NodeManager.h"

#define PTM_RATIO 32.0
USING_NS_CC;
Planet::Planet(void)
{
}


Planet::~Planet(void)
{
}

Planet* Planet::create(cocos2d::Vec2 position,b2World* world,Node *node)
{
	Planet * sprite = new Planet();
	if (sprite) {
		sprite->initPhysic(position,world,node);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Planet::initPhysic(cocos2d::Vec2 position,b2World* world,Node *node)
{
	float radius = (b2NodeManager::getInstance()->radius) / 2 / PTM_RATIO;
	float density = 0.4f;
	_mass = density * b2_pi * radius * radius;
	_world = world;
	_type = kPlanet;
	this->setPosition(position);
	this->setContentSize(Size(radius * 2 * PTM_RATIO,radius * 2 * PTM_RATIO));
	node->addChild(this,_type,kObject);
	/*Sprite *mainSprite = Sprite::create("Planet_1.png");
	mainSprite->setPosition(this->getContentSize()/2);
	this->addChild(mainSprite);*/

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
	bodyDef.userData = this;
	
	_body = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = radius; // mainSprite->getContentSize().width / 2 / PTM_RATIO;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;    
	fixtureDef.density = density;
	//fixtureDef.density = 2 / (circle.m_radius * circle.m_radius * 3.14);
	//fixtureDef.friction = 1.0f;
	//fixtureDef.restitution = 0.1f;
	//fixtureDef.isSensor = true;
	_body->CreateFixture(&fixtureDef); 

	//circle.m_radius = circle.m_radius/2;
	//fixtureDef.isSensor = false;
	//_body->CreateFixture(&fixtureDef); 
}

float Planet::getMass()
{
	return _mass;
}