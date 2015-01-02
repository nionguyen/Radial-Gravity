#ifndef __RagDoll__
#define __RagDoll__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "CCGL.h"

USING_NS_CC;

class RagDoll : public cocos2d::Node {
public:

    RagDoll();
    virtual ~RagDoll();
    bool init();
    void createPhysicsObject(b2World *world,Vec2 _ragDollPosition);
    CREATE_FUNC(RagDoll);
};

#endif
