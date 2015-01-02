#ifndef __B2_NODE_H__
#define __B2_NODE_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>

class b2Node : public cocos2d::Node
{
public:
	b2Node();
	virtual ~b2Node();
	virtual bool isDirty() const;

	/** Keep the sprite's rotation separate from the body. */
	bool isIgnoreBodyRotation() const;
	void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

	virtual b2Vec2 getPhysicPosition();
	virtual const cocos2d::Vec2& getPosition() const override;
	virtual void getPosition(float* x, float* y) const override;
	virtual float getPositionX() const override;
	virtual float getPositionY() const override;
	virtual void setPosition(const cocos2d::Vec2 &position) override;
	virtual float getRotation() const override;
	virtual void setRotation(float rotation) override;
	virtual void setVisible(bool visible) override;
	virtual float getMass();
	//virtual const cocos2d::Mat4& getNodeToParentTransform() const override;
	//virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentTransformFlags) override;

protected:
	bool    _ignoreBody;
	CC_SYNTHESIZE(b2Body *, _body, Body);
	CC_SYNTHESIZE(b2World *, _world, World);
};

#endif // __LFSPRITENODE_H__
