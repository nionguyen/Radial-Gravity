#ifndef _PHYSIC_DELEGATE_H__
#define _PHYSIC_DELEGATE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../Physic/GLES-Render.h"

USING_NS_CC;

class PhysicDelegate : public cocos2d::Layer
{
public:
	PhysicDelegate();
	virtual ~PhysicDelegate();
private:
	GLESDebugDraw * m_debugDraw;
	CC_SYNTHESIZE(b2World*, _world, World);
	CC_SYNTHESIZE(b2ContactListener*, _collisionListener, CollisitionListener);
protected:
	CustomCommand _customCmd;
	void onDraw(const Mat4 &transform, uint32_t flags);
public:
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
public:
	virtual void initWorld();
};

#endif