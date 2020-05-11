#include "GameSettingsMenu.h"

using namespace cocos2d;
using namespace ui;
using namespace cocos2d::experimental;
using namespace DEF_SETT;

cocos2d::Scene* GameSettingsMenu::createScene() {
	cocos2d::Scene* scene = cocos2d::Scene::create();
	auto layer = GameSettingsMenu::create();
	scene->addChild(layer);

	return scene;
}

bool GameSettingsMenu::init() {
	if (!Layer::init())
	{
		return false;
	}
	
	_soundVolume = _core->getSoundsVolume();
	_musicVolume = _core->getMusicVolume();


	auto winSize = Director::getInstance()->getWinSize();

	// Setting background
	auto background = cocos2d::Sprite::create("BG2HD.png");
	background->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(background, 0);

	// Setting box
	auto box = cocos2d::Sprite::createWithSpriteFrameName("SettingsBG.png");
	box->setAnchorPoint(Point::ANCHOR_MIDDLE);
	box->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(box, 1);

	////Adding SaveGameLabel label
	//auto saveGameLabel = Label::createWithTTF(SAVE_GAME_LABEL, FONT, LABEL_FONT_SIZE * 3);
	//saveGameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	//saveGameLabel->setColor(METALLIC_GOLD);
	//saveGameLabel->setPosition(winSize.width / 2, winSize.height / 2 + scrollView->getContentSize().height / 1.5f);
	//this->addChild(saveGameLabel, 2);

	_sliderSound = Slider::create();
	_sliderSound->loadBarTexture("BarTexture.png"); // what the slider looks like
	_sliderSound->loadSlidBallTextures("SlidBallTextures1.png", "SlidBallTextures2.png");
	_sliderSound->loadProgressBarTexture("ProgressBarTexture.png");
	_sliderSound->setMaxPercent(100);
	_sliderSound->setPercent(static_cast<int>(_soundVolume * 100.0f));
	_sliderSound->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	
	_sliderSound->setPosition(Vec2(winSize.width / 2 - _sliderSound->getContentSize().width / 4, winSize.height / 2 + _sliderSound->getContentSize().height * 1.5f));
	_sliderSound->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				AudioEngine::stop(_musicID);
				break;
			case ui::Widget::TouchEventType::MOVED:
				break;
			case ui::Widget::TouchEventType::ENDED:
				_soundVolume = static_cast<float>(_sliderSound->getPercent()) / 100.0f;
				AudioEngine::play2d(MOVE_SOUND_SAMPLE, false, _soundVolume);
				break;
			default:
				break;
		}
	});
	this->addChild(_sliderSound, 3);
	
	_sliderMusic = Slider::create();
	_sliderMusic->loadBarTexture("BarTexture.png"); // what the slider looks like
	_sliderMusic->loadSlidBallTextures("SlidBallTextures1.png", "SlidBallTextures2.png");
	_sliderMusic->loadProgressBarTexture("ProgressBarTexture.png");
	_sliderMusic->setMaxPercent(100);
	_sliderMusic->setPercent(static_cast<int>(_musicVolume * 100.0f));
	_sliderMusic->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	_sliderMusic->setPosition(Vec2(winSize.width / 2 - _sliderMusic->getContentSize().width / 4, winSize.height / 2 - _sliderMusic->getContentSize().height * 0.5f));
	_sliderMusic->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type) {	
			case ui::Widget::TouchEventType::BEGAN:
				AudioEngine::stop(_musicID);
				_musicID = AudioEngine::play2d(MUSIC_SAMPLE, false, _musicVolume);
				break;
			case ui::Widget::TouchEventType::MOVED:
				AudioEngine::setVolume(_musicID, static_cast<float>(_sliderMusic->getPercent()) / 100);
				break;
			case ui::Widget::TouchEventType::ENDED:
				_musicVolume = static_cast<float>(_sliderMusic->getPercent()) / 100;
				AudioEngine::setVolume(_musicID, _musicVolume);
				break;
			default:
				break;
		}
	});

	this->addChild(_sliderMusic, 3);

	//Adding buttons
	auto buttonSAVE = Button::create("Images/FloppyDiskIcon.png", "Images/FloppyDiskIcon2.png");
	buttonSAVE->setScale(0.8f);
	buttonSAVE->setPosition(Vec2(winSize.width / 2 - _sliderMusic->getContentSize().width / 4, winSize.height / 2 - _sliderMusic->getContentSize().width / 3));

	auto buttonEXIT = Button::create("Images/QuitIcon.png", "Images/QuitIcon2.png");
	buttonEXIT->setScale(0.8f);
	buttonEXIT->setPosition(Vec2(winSize.width / 2 + _sliderMusic->getContentSize().width / 4, winSize.height / 2 - _sliderMusic->getContentSize().width / 3));

	buttonSAVE->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			_core->setSoundsVolume(_soundVolume);
			_core->setMusicVolume(_musicVolume);
			AudioEngine::stop(_musicID);
			AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
			break;
		default:
			break;
		}
	});

	buttonEXIT->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			AudioEngine::stop(_musicID);
			AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
			_core->startTurnDurationCount();
			Director::getInstance()->popScene();
			break;
		default:
			break;
		}	
	});

	this->addChild(buttonSAVE, 2);
	this->addChild(buttonEXIT, 2);

	return true;
}
