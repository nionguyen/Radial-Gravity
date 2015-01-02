#include "b2NodeManager.h"
#include "../Common/GameConfig.h"
#include "../Common/ResourceDefine.h"
#include "b2PhysicObject.h"
#include "Planet.h"
#include "Ball.h"
#define PTM_RATIO 32.0
b2NodeManager::b2NodeManager(void)
{
	_nodes = std::make_shared<Vector<b2Node*>>();
	_planets = std::make_shared<Vector<b2Node*>>();
	_balls = std::make_shared<Vector<b2Node*>>();
	_deleteNodes = std::make_shared<Vector<b2Node*>>();
	_collisionListener = nullptr;
	mag = 700;
	radius = 100;
}


b2NodeManager::~b2NodeManager(void)
{
	_world = nullptr;
	_mainLayer = nullptr;
	_collisionListener = nullptr;

	_nodes->clear();
	_planets->clear();
	_balls->clear();
	_deleteNodes->clear();
}

static b2NodeManager *m_pInstance;

b2NodeManager* b2NodeManager::getInstance()
{
	if (m_pInstance == 0) {
		m_pInstance = new b2NodeManager();
	}
	return m_pInstance;
}

void b2NodeManager::addB2Node(b2Node *node)
{
	_nodes->pushBack(node);
	if(((b2PhysicObject *) node)->getType() == kPlanet)
	{
		_planets->pushBack(node);
	}
	if(((b2PhysicObject *) node)->getType() == kBall)
	{
		_balls->pushBack(node);
	}
}

void b2NodeManager::removeB2Node(b2Node *node)
{
	_nodes->eraseObject(node,true);
	_planets->eraseObject(node,true);
	_balls->eraseObject(node,true);
}

void b2NodeManager::addDeleteNode(b2Node *node)
{
	_deleteNodes->pushBack(node);
}

void b2NodeManager::clearAll()
{
	_nodes->clear();
	_planets->clear();
	_balls->clear();
	_deleteNodes->clear();
}



void b2NodeManager::update(float dt)
{
	_world->Step(dt, 8, 1);
	int size = _nodes->size();
	b2PhysicObject * node;

	for (int i = 0; i < size; i++) {
		node = (b2PhysicObject *) _nodes->at(i);
		if (node->isVisible())
			node->update(dt);
	}

	Planet * planet;
	Ball * ball;

	for (int i = 0; i < _balls->size(); i++) {
		ball = (Ball *) _balls->at(i);
		if (ball->isVisible())
		{
			ball->ClearGravitation();
			b2Vec2 position = ball->getPhysicPosition();

			for(int j = 0; j < _planets->size(); j++)
			{
				planet = (Planet *) _planets->at(j);
				b2Vec2 distance = planet->getPhysicPosition() - position;
				ball->AddGravitation(distance, planet->getMass());
			}

			ball->Process();
		}
	}

	for (int i = 0; i < _deleteNodes->size(); i++) {
		removeB2Node(_deleteNodes->at(i));
		_world->DestroyBody(_deleteNodes->at(i)->getBody());
		_deleteNodes->at(i)->removeFromParentAndCleanup(true);
	}
	_deleteNodes->clear();
}

void b2NodeManager::deleteNode(Vec2 pos)
{
	int size = _nodes->size();
	b2PhysicObject * node;

	for (int i = 0; i < size; i++) {
		node = (b2PhysicObject *) _nodes->at(i);
		if(node->getBoundingBox().containsPoint(pos))
		{
			this->addDeleteNode(node);
		}
	}
}