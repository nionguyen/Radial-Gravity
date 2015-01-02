#ifndef __B2_PLANET_H__
#define __B2_PLANET_H__
#include "b2PhysicObject.h"

class Planet : public b2PhysicObject
{
public:
	Planet(void);
	virtual ~Planet(void);
	static Planet* create(cocos2d::Vec2 position,b2World* world,cocos2d::Node *node);
	float _mass;
	virtual float getMass() override;
private:
	void initPhysic(cocos2d::Vec2 position,b2World* world,cocos2d::Node *node);
};
#endif
