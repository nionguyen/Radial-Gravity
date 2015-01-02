#include "PhysicLayer.h"
#include "../B2/Planet.h"
#include "../B2/Ball.h"
#include "../B2/b2NodeManager.h"
#include "../B2/RagDoll.h"

#include "../Common/GameConfig.h"
#include "CocosGUI.h"
using namespace ui;
#define PTM_RATIO 32.0
#define TagLabel 1001
#define TagLabel2 1002
#define TagLabel3 1003

PhysicLayer::PhysicLayer()
{
}


PhysicLayer::~PhysicLayer()
{
}

bool PhysicLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = CC_CALLBACK_2(PhysicLayer::onTouchesBegan, this);
	touchListener->onTouchesMoved = CC_CALLBACK_2(PhysicLayer::onTouchesMoved, this);
	touchListener->onTouchesEnded = CC_CALLBACK_2(PhysicLayer::onTouchesEnded, this);
	touchListener->onTouchesCancelled = CC_CALLBACK_2(PhysicLayer::onTouchesCancelled, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(PhysicLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	initWorld();

	auto label = Text::create("Planet","Arial",24);
	label->setColor(Color3B::BLACK);
	label->setPosition(Vec2(VISIBLESIZE.width/2,VISIBLESIZE.height - label->getContentSize().height));
	this->addChild(label,TagLabel,TagLabel);

	{
		auto label = Text::create("Mag:700","Arial",24);
		label->setColor(Color3B::BLACK);
		label->setPosition(Vec2(VISIBLESIZE.width/2 + 200,VISIBLESIZE.height - label->getContentSize().height));
		this->addChild(label,TagLabel2,TagLabel2);
	}

	{
		auto label = Text::create("Radius:100","Arial",24);
		label->setColor(Color3B::BLACK);
		label->setPosition(Vec2(VISIBLESIZE.width/2 + 400,VISIBLESIZE.height - label->getContentSize().height));
		this->addChild(label,TagLabel3,TagLabel3);
	}
	return true;
}

void PhysicLayer::update(float dt)
{
	timeSinceLastTap += dt;
	float fixDetaTime = 0.016f;
	b2NodeManager::getInstance()->update(fixDetaTime);
}

void PhysicLayer::addNewSpriteAtPosition(Vec2 p)
{
	CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
	auto label = static_cast<Text*>(this->getChildByTag(TagLabel));
	std::string string = label->getString();
	if(string == "Planet")
	{
		b2NodeManager::getInstance()->addB2Node(Planet::create(p,_world,this));
	}
	if(string == "Object")
	{
		b2NodeManager::getInstance()->addB2Node(Ball::create(p,_world,this));
	}
	if(string == "RAGDOLL")
	{
		RagDoll* node1 = RagDoll::create();
		node1->createPhysicsObject(_world,p);
		addChild(node1,1);
	}
}

void PhysicLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto label = static_cast<Text*>(this->getChildByTag(TagLabel));

	if(keyCode == EventKeyboard::KeyCode::KEY_Q)
	{
		label->setString("Planet");
	}

	if(keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		label->setString("Object");
	}
	if(keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		label->setString("DELETE");
	}
	if(keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		label->setString("RAGDOLL");
	}
	if(keyCode == EventKeyboard::KeyCode::KEY_1)
	{
		{
			b2NodeManager::getInstance()->mag -= 50;
			std::string string = (CCString::createWithFormat("Mag:%i", b2NodeManager::getInstance()->mag))->getCString();
			auto label2 = static_cast<Text*>(this->getChildByTag(TagLabel2));
			label2->setString(string);
		}
		
	}
	if(keyCode == EventKeyboard::KeyCode::KEY_2)
	{
		{
			b2NodeManager::getInstance()->mag += 50;
			std::string string = (CCString::createWithFormat("Mag:%i", b2NodeManager::getInstance()->mag))->getCString();
			auto label2 = static_cast<Text*>(this->getChildByTag(TagLabel2));
			label2->setString(string);
		}
	}

	if(keyCode == EventKeyboard::KeyCode::KEY_3)
	{
		{
			b2NodeManager::getInstance()->radius -= 50;
			std::string string = (CCString::createWithFormat("Radius:%i", b2NodeManager::getInstance()->radius))->getCString();
			auto label3 = static_cast<Text*>(this->getChildByTag(TagLabel3));
			label3->setString(string);
		}
	}

	if(keyCode == EventKeyboard::KeyCode::KEY_4)
	{
		{
			b2NodeManager::getInstance()->radius += 50;
			std::string string = (CCString::createWithFormat("Radius:%i", b2NodeManager::getInstance()->radius))->getCString();
			auto label3 = static_cast<Text*>(this->getChildByTag(TagLabel3));
			label3->setString(string);
		}
	}
}

void PhysicLayer::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	for ( auto &item: touches )
	{
		auto touch = item;
		auto location = touch->getLocation();
		bool isDoubleTap = false;
		if (timeSinceLastTap > 0 && timeSinceLastTap < 0.4f)
		{
			isDoubleTap = true;
			auto label = static_cast<Text*>(this->getChildByTag(TagLabel));
			std::string string = label->getString();
			if(string == "DELETE")
			{
				b2NodeManager::getInstance()->deleteNode(location);
			}
		}
		timeSinceLastTap = 0;
	}
}
void PhysicLayer::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}

void PhysicLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	for (auto& touch : touches)
	{
		if(!touch)
			break;

		auto location = touch->getLocation();
		addNewSpriteAtPosition( location );
	}
}

void PhysicLayer::onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}