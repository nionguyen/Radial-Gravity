#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "PhysicLayer.h"
USING_NS_CC;

class MainScene : public PhysicLayer
{
public:
	virtual void update(float dt) override;
public:
	virtual ~MainScene();
    static cocos2d::Scene* scene();
    virtual bool init();
    CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__