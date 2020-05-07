#include "GameMenu.h"
#include <string>
//#include "audio/include/SimpleAudioEngine.h";
//
//using namespace CocosDenshion;
using namespace cocos2d;



cocos2d::Scene* GameMenu::createScene()
{
	cocos2d::Scene* scene = cocos2d::Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);

	return scene;
}

void GameMenu::update(float deltaTime)
{

}

bool GameMenu::init()
{
	//
	if (!Layer::init())
	{
		return false;
	}

	// Getting windows size
	auto winSize = Director::getInstance()->getWinSize();

	// Setting position in the middle of the windows
	Vec2 position(winSize.width / 2, winSize.height / 2);

	// Setting our background
	// if resource is situated in Resource - U don't have to write whole path to it
	auto background = cocos2d::Sprite::create("GameMenuHD.png");
	background->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(background);

	//Creating button sprites for menu
	auto NewPvPlGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("NewPvPGameIcon.png");
	auto NewPvPlGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("NewPvPGameIcon2.png");
	auto NewPvPcGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("NewPvPcGameIcon.png");
	auto NewPvPcGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("NewPvPcGameIcon2.png");
	auto CustomGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("CustomGameIcon.png");
	auto CustomGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("CustomGameIcon2.png");
	auto LoadGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("LoadGameIcon3.png");
	auto LoadGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("LoadGameIcon4.png");
	auto GameSettingsButton1 = cocos2d::Sprite::createWithSpriteFrameName("SettingsIcon.png");
	auto GameSettingsButton2 = cocos2d::Sprite::createWithSpriteFrameName("SettingsIcon2.png");
	auto QuitGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("QuitIcon.png");
	auto QuitGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("QuitIcon2.png");

	



	//Creating MenuItem for NewPlayerVsPlayerGame button
	MenuItemSprite* NewPvPlGame = MenuItemSprite::create(NewPvPlGameButton1, NewPvPlGameButton2, CC_CALLBACK_1(GameMenu::onNewGamePvPlClick, this));
	NewPvPlGame->setPosition(Vec2(-100.0, 270.0));
	//Creating MenuItem for NewPlayerPCGame button
	MenuItemSprite* NewPvPCGame = MenuItemSprite::create(NewPvPcGameButton1, NewPvPcGameButton2, CC_CALLBACK_1(GameMenu::onNewGamePvPCClick, this));
	NewPvPCGame->setPosition(Vec2(100.0, 270.0));
	//Creating MenuItem for CustomGame button
	MenuItemSprite* CustomGame = MenuItemSprite::create(CustomGameButton1, CustomGameButton2, CC_CALLBACK_1(GameMenu::onCustomGameClick, this));
	CustomGame->setPosition(Vec2(-400.0, 270.0));
	//Creating MenuItem for LoadGame button
	MenuItemSprite* LoadGame = MenuItemSprite::create(LoadGameButton1, LoadGameButton2, CC_CALLBACK_1(GameMenu::onLoadGameClick, this));
	LoadGame->setPosition(Vec2(-300.0, 270.0));
	//Creating MenuItem for GameSettings button
	MenuItemSprite* GameSettings = MenuItemSprite::create(GameSettingsButton1, GameSettingsButton2, CC_CALLBACK_1(GameMenu::onGameSettingsClick, this));
	GameSettings->setPosition(Vec2(300.0, 270.0));
	//Creating MenuItem for QuitGame button
	MenuItemSprite* QuitGame = MenuItemSprite::create(QuitGameButton1, QuitGameButton2, CC_CALLBACK_1(GameMenu::onQuitGameClick, this));
	QuitGame->setPosition(Vec2(400.0, 270.0));
	
		
	//background->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());

	auto menu = Menu::create(NewPvPlGame, NewPvPCGame, CustomGame, LoadGame, GameSettings, QuitGame, nullptr);
		
	this->addChild(menu);

	// Play theme
	//Core::sharedCore()->setBackgroundMusic(music_theme, true);

	return true;
}

void GameMenu::onNewGamePvPlClick(cocos2d::Ref* sender)
{
	_core->initialSetup();
	Director::getInstance()->pushScene(TransitionCrossFade::create(1.0, NewGameLayer::createScene()));
}

void GameMenu::onNewGamePvPCClick(cocos2d::Ref* sender)
{
	//Director::getInstance()->popToSceneStackLevel(2);
}

void GameMenu::onCustomGameClick(cocos2d::Ref* sender)
{
	/*auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);*/
}

void GameMenu::onLoadGameClick(cocos2d::Ref* sender)
{
	/*auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);*/
}

void GameMenu::onGameSettingsClick(cocos2d::Ref* sender)
{
	/*auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);*/
}

void GameMenu::onQuitGameClick(cocos2d::Ref* sender)
{
	/*auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);*/
}




