#include "QuitGameScene.h"

using namespace cocos2d;
using namespace ui;
using namespace CocosDenshion;
using namespace DEF_SETT;

cocos2d::Scene* QuitGameScene::createScene() {
	cocos2d::Scene* scene = cocos2d::Scene::create();
	auto layer = QuitGameScene::create();
	scene->addChild(layer);

	return scene;
}

bool QuitGameScene::init() {
	//
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	// pause BackgroundMusic 
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	// Setting background
	auto background = cocos2d::Sprite::create("BG2HD.png");
	background->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(background, 0);

	auto box = cocos2d::Sprite::createWithSpriteFrameName("SettingsBox.png");
	box->setAnchorPoint(Point::ANCHOR_MIDDLE);
	box->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(box, 1);

	//Adding QuitGameLabel label
	auto quitGameLabel = Label::createWithTTF(QUIT_GAME_LABEL, FONT, LABEL_FONT_SIZE * 3);
	quitGameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	quitGameLabel->setColor(METALLIC_GOLD);
	quitGameLabel->setPosition(winSize.width / 2, winSize.height / 2 + 80);
	this->addChild(quitGameLabel, 2);

	//Adding buttons
	auto buttonYES = Button::create("Images/YesIcon.png", "Images/YesIcon2.png");
	buttonYES->setPosition(Vec2(winSize.width / 2 - 80, winSize.height / 2 - 30));

	auto buttonNO = Button::create("Images/QuitIcon.png", "Images/QuitIcon2.png");
	buttonNO->setPosition(Vec2(winSize.width / 2 + 80, winSize.height / 2 - 30));
	
	buttonYES->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		_core->clearData();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->popToRootScene();
	});
	
	buttonNO->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		_core->startTurnDurationCount();
		Director::getInstance()->popScene();
	});

	this->addChild(buttonYES, 2);
	this->addChild(buttonNO, 2);


	

	return true;
}

