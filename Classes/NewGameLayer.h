#pragma once


#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Core.h"
#include "SaveGameScene.h"
#include "QuitGameScene.h"

class NewGameLayer : public cocos2d::Layer {
private:
	Core* _core = Core::sharedCore();
	cocos2d::Label* _logMessageLabel;
	cocos2d::Label* _p1Timer;
	cocos2d::Label* _p2Timer;
	cocos2d::Sprite* _whiteKingIcon = nullptr;
	cocos2d::Sprite* _blackKingIcon = nullptr;
	cocos2d::ui::ScrollView* _scrollView = nullptr;
	cocos2d::Vector<cocos2d::ui::Text*> _playersMoves = cocos2d::Vector<cocos2d::ui::Text*>(50);

	void setActiveIcon();
	void updateTimers();

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(NewGameLayer);

	void processEvent(cocos2d::Vec2 location);

	void update(float deltaTime);

	void onMouseDown(cocos2d::Event* event);

	void onSaveGameClick(cocos2d::Ref* sender);

	void onLoadGameClick(cocos2d::Ref* sender);

	void onGameSettingsClick(cocos2d::Ref* sender);

	void onQuitGameClick(cocos2d::Ref* sender);

	
};
