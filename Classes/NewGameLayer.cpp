#include "NewGameLayer.h"

using namespace cocos2d;

cocos2d::Scene* NewGameLayer::createScene() {
	cocos2d::Scene* scene = cocos2d::Scene::create();
	auto layer = NewGameLayer::create();
	scene->addChild(layer);

	return scene;
}

bool NewGameLayer::init() {
	//
	if (!Layer::init())
	{
		return false;
	}

	// Getting windows size
	//auto winSize = Director::getInstance()->getWinSize();

	// Setting position in the middle of the windows
	//Vec2 center(winSize.width / 2, winSize.height / 2);

	// Setting background with desk (desk corner 73,104)
	auto background = cocos2d::Sprite::create("NewGameLayer.png");
		background->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
		this->addChild(background, 0);

	//Creating button sprites for menu
	auto SaveGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("FloppyDiskIcon.png");
	auto SaveGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("FloppyDiskIcon2.png");
	auto LoadGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("LoadGameIcon3.png");
	auto LoadGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("LoadGameIcon4.png");
	auto GameSettingsButton1 = cocos2d::Sprite::createWithSpriteFrameName("SettingsIcon.png");
	auto GameSettingsButton2 = cocos2d::Sprite::createWithSpriteFrameName("SettingsIcon2.png");
	auto QuitGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("QuitIcon.png");
	auto QuitGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("QuitIcon2.png");

	//Creating MenuItem for SaveGame button
	MenuItemSprite* SaveGame = MenuItemSprite::create(SaveGameButton1, SaveGameButton2, CC_CALLBACK_1(NewGameLayer::onSaveGameClick, this));
		SaveGame->setScale(0.8);
		SaveGame->setPosition(Vec2(236.0, 320.0));
	//Creating MenuItem for LoadGame button
	MenuItemSprite* LoadGame = MenuItemSprite::create(LoadGameButton1, LoadGameButton2, CC_CALLBACK_1(NewGameLayer::onLoadGameClick, this));
		LoadGame->setScale(0.8);
		LoadGame->setPosition(Vec2(314.0, 320.0));
	//Creating MenuItem for GameSettings button
	MenuItemSprite* GameSettings = MenuItemSprite::create(GameSettingsButton1, GameSettingsButton2, CC_CALLBACK_1(NewGameLayer::onGameSettingsClick, this));
		GameSettings->setScale(0.8);
		GameSettings->setPosition(Vec2(392.0, 320.0));
	//Creating MenuItem for QuitGame button
	MenuItemSprite* QuitGame = MenuItemSprite::create(QuitGameButton1, QuitGameButton2, CC_CALLBACK_1(NewGameLayer::onQuitGameClick, this));
		QuitGame->setScale(0.8);
		QuitGame->setPosition(Vec2(470.0, 320.0));

	auto menu = Menu::create(SaveGame, LoadGame, GameSettings, QuitGame, nullptr);
	this->addChild(menu);

	for (auto figure : *_core->getWhiteArmy()) {
		this->addChild(figure);
		figure->setGlobalZOrder(BOARD_SIZE - figure->getLocation().x);
	}

	for (auto figure : *_core->getBlackArmy()) {
		this->addChild(figure);
		figure->setGlobalZOrder(BOARD_SIZE - figure->getLocation().x);
	}

	//Handle Touch Events
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(NewGameLayer::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	



	return true;
}

void NewGameLayer::update(float deltaTime) {}

void NewGameLayer::onMouseDown(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	Vec2 globalLocation = mouseEvent->getLocationInView();

	Location boardLocation;

	float floatX = (globalLocation.y - BOARD_Y) / SQUARE_SIZE;
	if (floatX < 0 || floatX >= BOARD_SIZE) {
		return;
	}

	float floatY = (globalLocation.x - BOARD_X) / SQUARE_SIZE;
	if (floatY < 0 || floatY >= BOARD_SIZE) {
		return;
	}

	boardLocation.x = static_cast<int>(floatX);
	boardLocation.y = static_cast<int>(floatY);

	_core->processEvent(boardLocation);
}



void NewGameLayer::onSaveGameClick(cocos2d::Ref* sender)
{
	/*auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);*/
}

void NewGameLayer::onLoadGameClick(cocos2d::Ref* sender)
{
	/*auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);*/
}

void NewGameLayer::onGameSettingsClick(cocos2d::Ref* sender)
{
	/*auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);*/
}

void NewGameLayer::onQuitGameClick(cocos2d::Ref* sender)
{
	/*auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);*/
}
