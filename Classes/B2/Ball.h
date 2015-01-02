#ifndef __B2_BALL_H__
#define __B2_BALL_H__
#include "b2PhysicObject.h"

class Ball : public b2PhysicObject
{
public:
	Ball(void);
	virtual ~Ball(void);
	static Ball* create(cocos2d::Vec2 position,b2World* world,cocos2d::Node *node);

	void ClearGravitation();
	void AddGravitation(b2Vec2 distance, float mass);
	float GetGravityAngle();
	void Process();
private:
	void initPhysic(cocos2d::Vec2 position,b2World* world,cocos2d::Node *node);
	b2Vec2 gravitationalForce;
	//cocos2d::Vec2 oldPos;
};
#endif
