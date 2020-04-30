#pragma once

#include "cocos2d.h"
#include "Core.h";

class NewGameLayer : public cocos2d::Layer {
private:
	Core* _core = Core::sharedCore();
	
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(NewGameLayer);


	void update(float deltaTime);

	void onMouseDown(cocos2d::Event* event);

	void onSaveGameClick(cocos2d::Ref* sender);

	void onLoadGameClick(cocos2d::Ref* sender);

	void onGameSettingsClick(cocos2d::Ref* sender);

	void onQuitGameClick(cocos2d::Ref* sender);
};
