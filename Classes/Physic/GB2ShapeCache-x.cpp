//
//  Modified by Saket Sinha for cocos2d-x v3.2
// http://redtgames.com
//  GB2ShapeCache-x.cpp
//
//  Loads physics sprites created with http://www.PhysicsEditor.de
//  To be used with cocos2d-x
//
//  Generic Shape Cache for box2d
//
//  Created by Thomas Broquist
//
//      http://www.PhysicsEditor.de
//      http://texturepacker.com
//      http://www.code-and-web.de
//
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include "GB2ShapeCache-x.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

/**
 * Internal class to hold the fixtures
 */
class FixtureDef {
public:
    FixtureDef()
    : next(NULL) {}
    
    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }
    
    FixtureDef *next;
    b2FixtureDef fixture;
//    int callbackData;
};

class BodyDef {
public:
	BodyDef()
	: fixtures(NULL) {}
	
	~BodyDef() {
		if (fixtures)
			delete fixtures;
	}
	
	FixtureDef *fixtures;
	Point anchorPoint;
};

static GB2ShapeCache *_sharedGB2ShapeCache = NULL;

GB2ShapeCache* GB2ShapeCache::sharedGB2ShapeCache(void) {
	if (!_sharedGB2ShapeCache) {
		_sharedGB2ShapeCache = new GB2ShapeCache();
        _sharedGB2ShapeCache->init();
	}
	
	return _sharedGB2ShapeCache;
}

bool GB2ShapeCache::init() {
	return true;
}

void GB2ShapeCache::reset() {
	std::map<std::string, BodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
		delete iter->second;
	}
	shapeObjects.clear();
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *so = (*pos).second;
    
	FixtureDef *fix = so->fixtures;
    while (fix) {
        body->CreateFixture(&fix->fixture);
        fix = fix->next;
    }
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape,float scale) {
	/*if(scale == 1.0f)
	{
		addFixturesToBody(body,shape);
		return;
	}*/

	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());

	BodyDef *so = (*pos).second;

	FixtureDef *fix = so->fixtures;
	
	while (fix) {
		const b2Shape* shape = fix->fixture.shape;
		b2FixtureDef fixtureDef;
		b2FixtureDef oldFixtureDef = fix->fixture;
		if(shape->GetType() == b2Shape::e_circle )
		{
			b2CircleShape* oldCircle = (b2CircleShape*)fix->fixture.shape;
			b2CircleShape newCircle;
			newCircle.m_radius = oldCircle->m_radius * scale;
			newCircle.m_p = scale * oldCircle->m_p;
			fixtureDef.shape = &newCircle;
			fixtureDef.density = oldFixtureDef.density;
			fixtureDef.filter = oldFixtureDef.filter;
			fixtureDef.friction = oldFixtureDef.friction;
			fixtureDef.isSensor = oldFixtureDef.isSensor;
			fixtureDef.restitution = oldFixtureDef.restitution;
			fixtureDef.userData = oldFixtureDef.userData;
			body->CreateFixture(&fixtureDef);
		}
		if(shape->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape* polygon = (b2PolygonShape*)fix->fixture.shape;
			int count = polygon->GetVertexCount();
			b2Vec2 *m_newVertices = new b2Vec2[count];

			for(int i = 0;i<count;i++)
			{
				m_newVertices[i] = scale * polygon->GetVertex(i);
			}

			b2PolygonShape newPolygon;
			newPolygon.Set(m_newVertices, count);

			fixtureDef.shape = &newPolygon;
			fixtureDef.density = oldFixtureDef.density;
			fixtureDef.filter = oldFixtureDef.filter;
			fixtureDef.friction = oldFixtureDef.friction;
			fixtureDef.isSensor = oldFixtureDef.isSensor;
			fixtureDef.restitution = oldFixtureDef.restitution;
			fixtureDef.userData = oldFixtureDef.userData;
			body->CreateFixture(&fixtureDef);
		}
		fix = fix->next;
	}
}

cocos2d::Point GB2ShapeCache::anchorPointForShape(const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *bd = (*pos).second;
	return bd->anchorPoint;
}


void GB2ShapeCache::addShapesWithFile(const std::string &plist) {
    
	//const char *fullName = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist.c_str()).c_str();
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile((plist.c_str()));
    // not triggered - cocos2dx delivers empty dict if non was found
    
	//CCAssert(dict != NULL, "Shape-file not found");
    
    CCAssert(!dict.empty(), "plist file empty or not existing");
	
	ValueMap metadataDict = dict.at("metadata").asValueMap();
    
    int format = metadataDict.at("format").asInt();
    ptmRatio = metadataDict.at("ptm_ratio").asFloat();
    log("ptmRatio = %f",ptmRatio);
	CCAssert(format == 1, "Format not supported");
    
    
	ValueMap bodyDict = dict.at("bodies").asValueMap();
    
    b2Vec2 vertices[b2_maxPolygonVertices];

    std::string bodyName;
	ValueMap bodyData;
    //iterate body list
    for(auto dictElem : bodyDict)
    //CCDICT_FOREACH(bodyDict,dictElem )
    {
        bodyData = dictElem.second.asValueMap();
        bodyName = dictElem.first;
        
        BodyDef *bodyDef = new BodyDef();
        bodyDef->anchorPoint = PointFromString(bodyData.at("anchorpoint").asString());
        ValueVector fixtureList = bodyData.at("fixtures").asValueVector();
        FixtureDef **nextFixtureDef = &(bodyDef->fixtures);
        
        //iterate fixture list
        //Ref *arrayElem;
        for(auto arrayElem : fixtureList)
        //CCARRAY_FOREACH(fixtureList, arrayElem)
        {
            b2FixtureDef basicData;
            ValueMap fixtureData = arrayElem.asValueMap();
            
            basicData.filter.categoryBits = fixtureData.at("filter_categoryBits").asInt();
            
            basicData.filter.maskBits = fixtureData.at("filter_maskBits").asInt();
            basicData.filter.groupIndex = fixtureData.at("filter_groupIndex").asInt();
            basicData.friction = fixtureData.at("friction").asFloat();
            
            basicData.density = fixtureData.at("density").asFloat();
            
            basicData.restitution = fixtureData.at("restitution").asFloat();
            //CCLog("%s", static_cast<__String *>(fixtureData->objectForKey("id"))->getCString());
            //basicData.userData = __String::create(static_cast<__String *>(fixtureData->objectForKey("id"))->getCString())->retain();
            
            basicData.isSensor = fixtureData.at("isSensor").asBool();
            
//            string cb = fixtureData.at("userdataCbValue").asString();
            
//            int callbackData = 0;
            
//			if (cb != "")
//				callbackData =fixtureData.at("userdataCbValue").asInt();
            
			std::string fixtureType = fixtureData.at("fixture_type").asString();
            
			if (fixtureType == "POLYGON") {
                ValueVector polygonsArray = fixtureData.at("polygons").asValueVector();
				
                //Ref *dicArrayElem;
                for(auto dicArrayElem : polygonsArray)
                //CCARRAY_FOREACH(polygonsArray, dicArrayElem)
                {
                    FixtureDef *fix = new FixtureDef();
                    fix->fixture = basicData; // copy basic data
//                    fix->callbackData = callbackData;
                    
                    b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;
                    
                    ValueVector polygonArray = dicArrayElem.asValueVector();
                    
                    assert(polygonArray.capacity() <= b2_maxPolygonVertices);
                    
                    //Ref *piter;
                    for(auto piter : polygonArray)
                    //CCARRAY_FOREACH(polygonArray, piter)
                    {
                        string verStr = piter.asString();
                        Point offset = PointFromString(verStr);
                        vertices[vindex].x = (offset.x / ptmRatio) ;
                        vertices[vindex].y = (offset.y / ptmRatio) ;
                        vindex++;
                    }
                    
                    polyshape->Set(vertices, vindex);
                    fix->fixture.shape = polyshape;
                    
                    // create a list
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);
                }
                
                
			}
            else if (fixtureType == "CIRCLE") {
				FixtureDef *fix = new FixtureDef();
                fix->fixture = basicData; // copy basic data
//                fix->callbackData = callbackData;
                
                ValueMap circleData = fixtureData.at("circle").asValueMap();
                
                b2CircleShape *circleShape = new b2CircleShape();
				
                circleShape->m_radius = circleData.at("radius").asFloat() / ptmRatio;
				Point p = PointFromString(circleData.at("position").asString());
                circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                fix->fixture.shape = circleShape;
				
                // create a list
                *nextFixtureDef = fix;
                nextFixtureDef = &(fix->next);
                
			}
            else {
				CCAssert(0, "Unknown fixtureType");
			}
		}
        // add the body element to the hash
        shapeObjects[bodyName] = bodyDef;
        
    }
    
}