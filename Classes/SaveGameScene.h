#pragma once


#include "cocos2d.h"
#include "Core.h"
#include "ui/CocosGUI.h"
#include <fstream>
#include <filesystem> // creating directory for Saved Games and loading file with saved data

#include "NewGameLayer.h"
#include "Specification.h"



class SaveGameScene : public cocos2d::Layer {
private:
	Core* _core = Core::sharedCore();
	cocos2d::Vector<cocos2d::ui::Text*> _exsistingFiles = cocos2d::Vector<cocos2d::ui::Text*>(10);
	cocos2d::ui::ScrollView* _scrollView = nullptr;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SaveGameScene);

	void onMouseDown(cocos2d::Event* event);

};
