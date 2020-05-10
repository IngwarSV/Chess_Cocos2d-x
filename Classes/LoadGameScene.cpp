#include "LoadGameScene.h"

using namespace cocos2d;
using namespace ui;
using namespace CocosDenshion;
using namespace DEF_SETT;
namespace fs = std::filesystem;

cocos2d::Scene* LoadGameScene::createScene() {
	cocos2d::Scene* scene = cocos2d::Scene::create();
	auto layer = LoadGameScene::create();
	scene->addChild(layer, 0, "LoadGameScene");

	return scene;
}

bool LoadGameScene::init() {
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

	// Setting box
	auto box = cocos2d::Sprite::createWithSpriteFrameName("Save_LoadBox.png");
	box->setAnchorPoint(Point::ANCHOR_MIDDLE);
	box->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(box, 1);

	//Adding ScrollView for existing files
	auto scrollView = cocos2d::ui::ScrollView::create();
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setAnchorPoint(Point::ANCHOR_MIDDLE);
	scrollView->setContentSize(Size(box->getContentSize().width / 2, box->getContentSize().height / 3.2f));
	scrollView->setBackGroundColorType(ui::ScrollView::BackGroundColorType::NONE);
	scrollView->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	scrollView->setInnerContainerSize(Size(scrollView->getContentSize().width, scrollView->getContentSize().height));
	scrollView->setBounceEnabled(false);
	scrollView->setInertiaScrollEnabled(false);
	scrollView->setScrollBarEnabled(true);
	scrollView->setScrollBarPositionFromCorner(Vec2(LABEL_DISTANCE * 2, LABEL_DISTANCE / 2));
	scrollView->setScrollBarAutoHideTime(1.0f);
	scrollView->setScrollBarWidth(10);
	scrollView->setScrollBarColor(METALLIC_GOLD);
	scrollView->setScrollBarOpacity(255);
	this->addChild(scrollView, 2);

	//Adding LoadGameLabel label
	auto loadGameLabel = Label::createWithTTF(LOAD_GAME_LABEL, FONT, LABEL_FONT_SIZE * 3);
	loadGameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	loadGameLabel->setColor(METALLIC_GOLD);
	loadGameLabel->setPosition(winSize.width / 2, winSize.height / 2 + scrollView->getContentSize().height / 1.5f);
	this->addChild(loadGameLabel, 2);

	//Adding TextField
	auto plank = Sprite::createWithSpriteFrameName("Plank.png");
	plank->setAnchorPoint(Point::ANCHOR_MIDDLE);
	plank->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - scrollView->getContentSize().height / 1.6f));
	_textField = TextField::create("", FONT, LABEL_FONT_SIZE * 1.2f);
	_textField->setColor(METALLIC_GOLD);
	_textField->setCursorEnabled(true);
	_textField->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_textField->setPosition(Vec2(plank->getContentSize().width / 2, plank->getContentSize().height / 2));
	_textField->setHighlighted(true);
	_textField->setPlaceHolder(PLACEHOLDER_SAVE_GAME);
	_textField->setPlaceHolderColor(METALLIC_GOLD);
	_textField->setMaxLengthEnabled(true);
	_textField->setMaxLength(16);
	plank->addChild(_textField);
	this->addChild(plank, 4);

	//creating / checking for existing SavedGameDirectory
	std::string SavedGamesDir = FileUtils::getInstance()->getWritablePath();
	SavedGamesDir += SAVED_GAMES_DIR;
	if (!FileUtils::getInstance()->isDirectoryExist(SavedGamesDir)) {
		FileUtils::getInstance()->createDirectory(SavedGamesDir);
	}

	// creating buttons with existing filenames, adding them to scrollView
	cocos2d::Vector<cocos2d::ui::Button*> exsistingFiles = cocos2d::Vector<cocos2d::ui::Button*>(10);
	
	for (auto& files : fs::directory_iterator(SavedGamesDir)) {
		exsistingFiles.pushBack(Button::create("Images/Plank.png", "Images/Plank2.png"));
		auto button = exsistingFiles.back();
		button->setTitleText(files.path().filename().string());
		button->setTitleColor(METALLIC_GOLD);
		button->setTitleFontName(FONT);
		button->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
		button->setAnchorPoint(Point::ANCHOR_MIDDLE);
		button->setTitleFontSize(LABEL_FONT_SIZE * 1.2f);
		const float coordY = scrollView->getInnerContainerSize().height -
			LABEL_DISTANCE * (((exsistingFiles.size() - 1.0f) * 2.0f) + 0.7f);
		button->setPosition(Vec2(scrollView->getInnerContainer()->getContentSize().width / 2, coordY));
		//// Increasing innerContainer if needed
		if (button->getPosition().y - LABEL_DISTANCE * 2 < 0) {
			const float delta = scrollView->getContentSize().height;
			const float size = scrollView->getInnerContainer()->getContentSize().height + delta;
			scrollView->setInnerContainerSize(Size(scrollView->getInnerContainerSize().width, size));
			for (auto it = exsistingFiles.begin(); it != exsistingFiles.end(); ++it) {
				(*it)->setPositionY((*it)->getPosition().y + delta);
			}
		}
		button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				_textField->setString(dynamic_cast<ui::Button*>(sender)->getTitleText());
				break;
			default:
				break;
			}
		});
		scrollView->addChild(button, 3);
	}

	//Adding button to save game
	auto buttonPlay = Button::create("Images/PlayButt.png", "Images/PlayButt2.png");
	buttonPlay->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	buttonPlay->setPosition(Vec2(winSize.width / 2 +
		plank->getContentSize().width / 2 + 10, plank->getPosition().y));

	buttonPlay->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		std::string filename = _textField->getString();

		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (filename != "") {
				size_t length = filename.length();
				if (length > 4) {
					if (filename.substr(length - 4, 4) != ".txt") {
						filename += ".txt";
					}
				}
				else {
					filename += ".txt";
				}

				std::string filenamePath = FileUtils::getInstance()->getWritablePath() +
					SAVED_GAMES_DIR + '/' + filename;

				std::ifstream load(filenamePath);
				if (load) {
					std::string gameDataString;
					std::string wArmyDataString;
					std::string bArmyDataString;

					std::getline(load, gameDataString);
					std::getline(load, wArmyDataString);
					std::getline(load, bArmyDataString);

					_core->loadData(gameDataString, wArmyDataString, bArmyDataString, filename);
					load.close();

					Director::getInstance()->popToRootScene();
					Director::getInstance()->pushScene(TransitionCrossFade::create(1.0, NewGameLayer::createScene()));
				}
				else {
					_core->setLogMessage(NoSuchLoadFileString + filename);
					SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
					_core->startTurnDurationCount();
					Director::getInstance()->popScene();
				}
			}
			break;
		default:
			break;
		}
	});
	this->addChild(buttonPlay, 3);

	//Adding button to quit saving
	auto buttonQuit = Button::create("Images/QuitIcon.png", "Images/QuitIcon2.png");
	buttonQuit->setScale(0.8f);
	buttonQuit->setPosition(Vec2(winSize.width - 50, winSize.height - 50));

	buttonQuit->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		_core->startTurnDurationCount();
		Director::getInstance()->popScene();
	});

	this->addChild(buttonQuit, 3);

	return true;
}
