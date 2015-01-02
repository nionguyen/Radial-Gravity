#include "MainScene.h"
#include "../Common/GameConfig.h"
#include "../Common/ResourceDefine.h"
#include "../B2/b2PhysicObject.h"
#include "../B2/b2NodeManager.h"

#define PTM_RATIO 32.0

MainScene::~MainScene()
{

}



Scene* MainScene::scene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !PhysicLayer::init() )
    {
        return false;
    }
	{
		this->addChild(LayerColor::create(Color4B::WHITE),-100);
		this->scheduleUpdate();
	}

	b2NodeManager::getInstance()->setCollisionListener(nullptr);
	b2NodeManager::getInstance()->setMainLayer(this);
	b2NodeManager::getInstance()->setWorld(_world);


    return true;
}

void MainScene::update(float dt)
{
	PhysicLayer::update(dt);
}

