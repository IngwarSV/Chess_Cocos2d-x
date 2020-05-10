#pragma once


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "audio/include/SimpleAudioEngine.h"
#include <filesystem> // creating directory for Saved Games and loading file with saved data

#include "Core.h"
#include "NewGameLayer.h"
#include "Specification.h"



class SaveGameScene : public cocos2d::Layer {
private:
	Core* _core = Core::sharedCore();
	cocos2d::ui::TextField* _textField = nullptr;

public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(SaveGameScene);
};
