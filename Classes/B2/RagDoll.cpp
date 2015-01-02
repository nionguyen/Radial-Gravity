

#include "RagDoll.h"

#define PTM_RATIO 32.f

RagDoll::RagDoll()
{

}

RagDoll::~RagDoll() {
}

bool RagDoll::init() {
    
    if (!CCNode::init()) {
        return false;
    }
  
    return true;
}

float ptm(float value)
{
	return value/PTM_RATIO;
}
void RagDoll::createPhysicsObject(b2World *world,Vec2 _ragDollPosition)
{
	float degrees = -CC_DEGREES_TO_RADIANS(90);
	float rotation = -CC_DEGREES_TO_RADIANS(90);
	b2Vec2 newPos;
	b2Vec2 oldPos;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;

	b2PolygonShape box;
	b2FixtureDef fixtureDef;
	
	// Head ------
	b2CircleShape headShape;
	headShape.m_radius = ptm(12.5f);
	fixtureDef.shape = &headShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.3f;
	bd.position.Set(ptm(_ragDollPosition.x), ptm(_ragDollPosition.y));
	b2Body *head = world->CreateBody(&bd);
	head->CreateFixture(&fixtureDef);
	//head->ApplyLinearImpulse(b2Vec2(50.0f, 50.0f), head->GetWorldCenter(),true);
	oldPos = head->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	head->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// -----------

	// Torso1 ----
	box.SetAsBox(ptm(15.0f), ptm(10.0f));
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.1f;
	bd.position.Set(ptm(_ragDollPosition.x), ptm(_ragDollPosition.y + 25.0f));
	b2Body *torso1 = world->CreateBody(&bd);
	torso1->CreateFixture(&fixtureDef);
	oldPos = torso1->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	torso1->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);
	// -----------

	// Torso2 ----
	box.SetAsBox(ptm(15.0f), ptm(10.0f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x), ptm(_ragDollPosition.y + 43.0f));
	b2Body *torso2 = world->CreateBody(&bd);
	torso2->CreateFixture(&fixtureDef);
	oldPos = torso2->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	torso2->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);
	// -----------

	// Torso3 ----
	box.SetAsBox(ptm(15.0f), ptm(10.0f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x), ptm(_ragDollPosition.y + 58.0f));
	b2Body *torso3 = world->CreateBody(&bd);
	torso3->CreateFixture(&fixtureDef);
	oldPos = torso3->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	torso3->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);
	// -----------

	// UpperArm --
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.1f;

	// Left
	box.SetAsBox(ptm(18.0f), ptm(6.5f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x - 30.0f), ptm(_ragDollPosition.y + 20.0f));
	b2Body *upperArmL = world->CreateBody(&bd);
	upperArmL->CreateFixture(&fixtureDef);
	oldPos = upperArmL->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	upperArmL->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// Right
	box.SetAsBox(ptm(18.0f), ptm(6.5f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x + 30.0f), ptm(_ragDollPosition.y + 20.0f));
	b2Body *upperArmR = world->CreateBody(&bd);
	upperArmR->CreateFixture(&fixtureDef);
	oldPos = upperArmR->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	upperArmR->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// -----------

	// Lower Arm
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.1f;

	// Left
	box.SetAsBox(ptm(17.0f), ptm(6.0f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x - 57.0f), ptm(_ragDollPosition.y + 20.0f));
	b2Body *lowerArmL = world->CreateBody(&bd);
	lowerArmL->CreateFixture(&fixtureDef);
	oldPos = lowerArmL->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	lowerArmL->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// Right
	box.SetAsBox(ptm(17.0f), ptm(6.0f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x + 57.0f), ptm(_ragDollPosition.y + 20.0f));
	b2Body *lowerArmR = world->CreateBody(&bd);
	lowerArmR->CreateFixture(&fixtureDef);
	oldPos = lowerArmR->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	lowerArmR->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// -----------

	// UpperLeg --
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.1f;

	// Left
	box.SetAsBox(ptm(7.5f), ptm(22.0f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x - 8.0f), ptm(_ragDollPosition.y + 85.0f));
	b2Body *upperLegL = world->CreateBody(&bd);
	upperLegL->CreateFixture(&fixtureDef);
	oldPos = upperLegL->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	upperLegL->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// Right
	box.SetAsBox(ptm(7.5f), ptm(22.0f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x + 8.0f), ptm(_ragDollPosition.y + 85.0f));
	b2Body *upperLegR = world->CreateBody(&bd);
	upperLegR->CreateFixture(&fixtureDef);
	oldPos = upperLegR->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	upperLegR->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// -----------

	// LowerLeg --
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.1f;

	// Left
	box.SetAsBox(ptm(6.0f), ptm(20.0f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x - 8.0f), ptm(_ragDollPosition.y + 120.0f));
	b2Body *lowerLegL = world->CreateBody(&bd);
	lowerLegL->CreateFixture(&fixtureDef);
	oldPos = lowerLegL->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	lowerLegL->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// Right
	box.SetAsBox(ptm(6.0f), ptm(20.0f));
	fixtureDef.shape = &box;
	bd.position.Set(ptm(_ragDollPosition.x + 8.0f), ptm(_ragDollPosition.y + 120.0f));
	b2Body *lowerLegR = world->CreateBody(&bd);
	lowerLegR->CreateFixture(&fixtureDef);
	oldPos = lowerLegR->GetPosition() - b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO) ;
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	lowerLegR->SetTransform(newPos + b2Vec2(_ragDollPosition.x / PTM_RATIO, _ragDollPosition.y /PTM_RATIO),rotation);

	// -----------

	// -------------------------
	// Joints ------------------
	// -------------------------
	
	b2RevoluteJointDef jd;
	jd.enableLimit = true;

	// Head to shoulders
	jd.lowerAngle = -40.0f / (180.0f / M_PI) + 0;
	jd.upperAngle = 40.0f / (180.0f / M_PI) + 0;

	oldPos = b2Vec2(0.0f,15.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(torso1, head, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);
	
	
	// Upper arm to shoulders --
	// Left
	jd.lowerAngle = (-85.0f + 90) / (180.0f / M_PI) - 0;
	jd.upperAngle = (130.0f + 90) / (180.0f / M_PI) - 0;

	oldPos = b2Vec2(-18.0f,20.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(torso1, upperArmL, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);

	// Right
	jd.lowerAngle = (-130.0f + 90) / (180.0f / M_PI) - 0;
	jd.upperAngle = (85.0f + 90) / (180.0f / M_PI) - 0;

	oldPos = b2Vec2(18.0f,20.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(torso1, upperArmR, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);
	return;
	// -------------------------

	// Lower arm to shoulders --
	// Left
	jd.lowerAngle = (-130.0f + 90) / (180.0f / M_PI);
	jd.upperAngle = (10.0f + 90) / (180.0f / M_PI);

	oldPos = b2Vec2(-45.0f,20.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(upperArmL, lowerArmL, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);

	// Right
	jd.lowerAngle = (-10.0f + 90) / (180.0f / M_PI) + rotation;
	jd.upperAngle = (130.0f + 90) / (180.0f / M_PI) + rotation;

	oldPos = b2Vec2(45.0f,20.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(upperArmR, lowerArmR, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);

	// -------------------------

	// Shoulders / stomach -----
	jd.lowerAngle = (-15.0f + 90) / (180.0f / M_PI) - rotation;
	jd.upperAngle = (15.0f + 90) / (180.0f / M_PI) - rotation;

	oldPos = b2Vec2(0.0f,35.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(torso1, torso2, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);

	// Stomach / hips
	jd.lowerAngle = (-0 + 90) / (180.0f / M_PI);
	jd.upperAngle = (-0 + 90) / (180.0f / M_PI);
	oldPos = b2Vec2(0.0f,50.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(torso2, torso3, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);

	// -------------------------

	// Torso to upper leg ------
	// Left
	jd.lowerAngle = (-25.0f + 90) / (180.0f / M_PI) - rotation;
	jd.upperAngle = (45.0f + 90) / (180.0f / M_PI) - rotation;

	oldPos = b2Vec2(-8.0f,72.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(torso3, upperLegL, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);

	// Right
	jd.lowerAngle = (-45.0f + 90) / (180.0f / M_PI) - rotation;
	jd.upperAngle = (25.0f + 90) / (180.0f / M_PI) - rotation;

	oldPos = b2Vec2(8.0f,72.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(torso3, upperLegR, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);

	// -------------------------

	// Upper leg to lower leg --
	// Left
	jd.lowerAngle = (-25.0f + 90) / (180.0f / M_PI) - rotation;
	jd.upperAngle = (115.0f + 90) / (180.0f / M_PI) - rotation;

	oldPos = b2Vec2(-8.0f,105.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(upperLegL, lowerLegL, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);

	// Right
	jd.lowerAngle = (-115.0f + 90) / (180.0f / M_PI) - rotation;
	jd.upperAngle = (25.0f + 90) / (180.0f / M_PI) - rotation;

	oldPos = b2Vec2(8.0f,105.0f);
	newPos.x = oldPos.x * cos(degrees) - oldPos.y * sin(degrees);
	newPos.y = oldPos.x * sin(degrees) + oldPos.y * cos(degrees);
	jd.Initialize(upperLegR, lowerLegR, b2Vec2(ptm(_ragDollPosition.x + newPos.x), ptm(_ragDollPosition.y + newPos.y)));
	world->CreateJoint(&jd);
}