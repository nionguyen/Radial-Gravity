#ifndef _PHYSIC_LAYER_H__
#define _PHYSIC_LAYER_H__

#include "PhysicDelegate.h"

class PhysicLayer : public PhysicDelegate
{
public:
	PhysicLayer();
	virtual ~PhysicLayer();
	virtual bool init();
public:
	virtual void update(float dt) override;
protected:
	void addNewSpriteAtPosition(Vec2 p);
	void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	float timeSinceLastTap;
};

#endif