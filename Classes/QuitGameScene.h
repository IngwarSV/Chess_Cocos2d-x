#pragma once


#include "cocos2d.h"
#include "Core.h"
#include "ui/CocosGUI.h"

#include "NewGameLayer.h"
#include "Specification.h"


class QuitGameScene : public cocos2d::Layer {
private:
	Core* _core = Core::sharedCore();
	
	
	


public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(QuitGameScene);

};
