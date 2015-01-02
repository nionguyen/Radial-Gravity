#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

enum {
	kBackground = -6,
	kMiddleground = -5,
	kForeground = -4,
	kObject = -3,
	kTut = -2,
	kButton = -1,
};

enum kPhysicObject {
	kPlanet = 1,
	kBall = 10,
};

#define VISIBLESIZE Director::getInstance()->getVisibleSize()
#define HALF_EXTRA_WIDTH ((VISIBLESIZE.width - VISIBLESIZE.height * 960 / 640) / 2)

#endif

