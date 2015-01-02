#ifndef _B2NODE_MANAGER_H__
#define _B2NODE_MANAGER_H__

#include "b2Node.h"
#include "../Scene/MainScene.h"

class b2NodeManager
{
private:
	b2NodeManager(void);
	CC_SYNTHESIZE(b2World *, _world, World);	
	CC_SYNTHESIZE(MainScene*, _mainLayer, MainLayer);
	CC_SYNTHESIZE(b2ContactListener*, _collisionListener, CollisionListener);
	std::shared_ptr<Vector<b2Node*>> _nodes;
	std::shared_ptr<Vector<b2Node*>> _planets;
	std::shared_ptr<Vector<b2Node*>> _balls;
	std::shared_ptr<Vector<b2Node*>> _deleteNodes;
public:
	~b2NodeManager(void);
	static b2NodeManager* getInstance();
public:
	void addB2Node(b2Node *node);
	void removeB2Node(b2Node *node);
	void addDeleteNode(b2Node *node);
	void clearAll();
	int mag;
	int radius;
public:
	void update(float dt);
	void deleteNode(Vec2 pos);
};

#endif //_B2NODE_MANAGER_H__
