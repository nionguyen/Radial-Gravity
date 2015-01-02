#ifndef _PHYSIC_OBJECT_H__
#define _PHYSIC_OBJECT_H__
#include "b2Node.h"
class b2PhysicObject : public b2Node
{
public:
	b2PhysicObject();
	virtual ~b2PhysicObject();
	virtual void update(float dt) override;
	CC_SYNTHESIZE(int, _type, Type);
};

#endif