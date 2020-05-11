#include "NewGameLayer.h"

//#define PERFORM_TESTS 1

using namespace cocos2d;
using namespace cocos2d::experimental;
namespace fs = std::filesystem;
using namespace DEF_SETT;
//using namespace CocosDenshion;

cocos2d::Scene* NewGameLayer::createScene() {
	cocos2d::Scene* scene = cocos2d::Scene::create();
	auto layer = NewGameLayer::create();
	scene->addChild(layer);

	return scene;
}

bool NewGameLayer::init() {
	if (!Layer::init())
	{
		return false;
	}

	// Getting windows size
	auto winSize = Director::getInstance()->getWinSize();

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
		SaveGame->setScale(0.8f);
		SaveGame->setPosition(SAVE_GAME_BUT);
	//Creating MenuItem for LoadGame button
	MenuItemSprite* LoadGame = MenuItemSprite::create(LoadGameButton1, LoadGameButton2, CC_CALLBACK_1(NewGameLayer::onLoadGameClick, this));
		LoadGame->setScale(0.8f);
		LoadGame->setPosition(LOAD_GAME_BUT);
	//Creating MenuItem for GameSettings button
	MenuItemSprite* GameSettings = MenuItemSprite::create(GameSettingsButton1, GameSettingsButton2, CC_CALLBACK_1(NewGameLayer::onGameSettingsClick, this));
		GameSettings->setScale(0.8f);
		GameSettings->setPosition(GAME_SETT_BUT);
	//Creating MenuItem for QuitGame button
	MenuItemSprite* QuitGame = MenuItemSprite::create(QuitGameButton1, QuitGameButton2, CC_CALLBACK_1(NewGameLayer::onQuitGameClick, this));
		QuitGame->setScale(0.8f);
		QuitGame->setPosition(QUIT_BUT);

	auto menu = Menu::create(SaveGame, LoadGame, GameSettings, QuitGame, nullptr);
	this->addChild(menu);

	//Adding ScrollView for movesLog (BUTTONS?????)
	_scrollView = cocos2d::ui::ScrollView::create();
	_scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	_scrollView->setContentSize(SCROLL_VIEW_SIZE);
	_scrollView->setBackGroundColorType(ui::ScrollView::BackGroundColorType::NONE);
	_scrollView->setPosition(SCROLL_VIEW_POS);
	_scrollView->setInnerContainerSize(Size(SCROLL_VIEW_SIZE.width, winSize.height));
	float CoordY = (_scrollView->getInnerContainerSize().height - _scrollView->getContentSize().height) * (-1);
	_scrollView->setInnerContainerPosition(Vec2(0.0f, CoordY));
	_scrollView->setBounceEnabled(false);
	_scrollView->setInertiaScrollEnabled(false);
	_scrollView->setScrollBarEnabled(true);
	//_scrollView->setScrollBarAutoHideTime(winSize.height);
	_scrollView->setScrollBarWidth(10);
	_scrollView->setScrollBarPositionFromCorner(Vec2(14, 15));
	_scrollView->setScrollBarColor(METALLIC_GOLD);
	_scrollView->setScrollBarOpacity(255);
	//// Adding "Game started!" string to ScrollView
	auto textWidget = ui::Text::create();
	textWidget->setString(GAME_STARTED_STRING);
	textWidget->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	textWidget->setFontName(FONT);
	textWidget->setFontSize(LABEL_FONT_SIZE);
	textWidget->setColor(METALLIC_GOLD);
	textWidget->setPosition(Vec2(labelCoordX, _scrollView->getInnerContainerSize().height - LABEL_DISTANCE));
	_playersMoves.pushBack(textWidget);
	_scrollView->addChild(textWidget);
	this->addChild(_scrollView, 1);

#if PERFORM_TESTS     // if PERFORM_TESTS - Loading saved games will just start simple new game
	//adding testsResults to scrollView
	MyTests tests;
	tests.runCoreTests();

	for (auto testsResult : _core->_testsResults) {
		updateMovesLog(testsResult);
	}
	_core->_testsResults.clear();
	
#endif

	//updating scrollViewContent in case of loading game
	for (auto lastMove : *(_core->getMovesVector())) {
		std::string text = (lastMove[0] == 'W') ? WHITE_PL_STRING : BLACK_PL_STRING;
		text += lastMove.substr(2, 5) + '\t' + lastMove.substr(7, 5);

		updateMovesLog(text);
	}

	// adding figures on the board
	for (auto figure : *_core->getWhiteArmy()) {
		this->addChild(figure, BOARD_SIZE - figure->getLocation().x);
	}

	for (auto figure : *_core->getBlackArmy()) {
		this->addChild(figure, BOARD_SIZE - figure->getLocation().x);
	}

	//Adding logMessages label
	_logMessageLabel = Label::createWithTTF(_core->getLogMessage(), FONT, LABEL_DISTANCE);
	_logMessageLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	_logMessageLabel->setColor(METALLIC_GOLD);
	_logMessageLabel->setPosition(LOG_MESS_POS);
	this->addChild(_logMessageLabel, 100);

	//Adding Timers labels
	_p1Timer = Label::createWithTTF("00:00", "fonts/royal-serif.ttf", 22);
	_p1Timer->setAnchorPoint(Vec2(0.0f, 0.0f));
	_p1Timer->setColor(METALLIC_GOLD);
	_p1Timer->setPosition(TIMER1_POS);
	this->addChild(_p1Timer, 100);

	_p2Timer = Label::createWithTTF("00:00", "fonts/royal-serif.ttf", 20);
	_p2Timer->setAnchorPoint(Vec2(0.0f, 0.0f));
	_p2Timer->setColor(METALLIC_GOLD);
	_p2Timer->setPosition(TIMER2_POS);
	this->addChild(_p2Timer, 100);

	//Adding ActiveSide sprites
	_whiteKingIcon = Sprite::createWithSpriteFrameName(WK_ACT_ICON);
	_whiteKingIcon->setPosition(ACT_SIDE_POS1);
	this->addChild(_whiteKingIcon, 100);
	_blackKingIcon = Sprite::createWithSpriteFrameName(BK_PAS_ICON);
	_blackKingIcon->setPosition(ACT_SIDE_POS2);
	this->addChild(_blackKingIcon, 100);

	

	//Handle Touch Events
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(NewGameLayer::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	

	// Launching update method every frame
	scheduleUpdate();

	// Setting SideToMoveIcon
	setActiveIcon();
	
	// Play BackgroundMusic
	/*SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic(CHESS_CLOCK.c_str(), true);*/
	//AudioEngine::stopAll();
	_layerMusicID = AudioEngine::play2d(CHESS_CLOCK, true, _core->getSoundsVolume());

	// Starting first turn
	_core->startTurnDurationCount();

	return true;
}

void NewGameLayer::loadGame(std::string filenamePath, std::string filename)
{
	//std::ifstream load(filenamePath);
	//if (load) {
	//	// deleting existing game data, executing initial setup in core
	//	/*_core->clearData();
	//	_core->initialSetup();*/
	//	
	//	// setting gameDuration
	//	std::pair<double, double> gameDuration;
	//	load >> gameDuration.first;
	//	load >> gameDuration.second;
	//	_core->setGameDuration(gameDuration);
	//	// MAKING all saved moves
	//	std::string savedMove;
	//	//std::getline(load, savedMove);
	//	while (!load.eof()) {
	//		savedMove = "";
	//		//std::getline(load, savedMove);
	//		load >> savedMove;
	//		if (savedMove.length() != 12) {
	//			continue; 
	//		}
	//		Location figureCurrentPosition;
	//		Location figureNewPosition;
	//		
	//		figureCurrentPosition.x = static_cast<int>(savedMove[3] - '1');
	//		figureCurrentPosition.y = static_cast<int>(savedMove[2] - 'A');
	//		figureNewPosition.x = static_cast<int>(savedMove[6] - '1');
	//		figureNewPosition.y = static_cast<int>(savedMove[5] - 'A');

	//		_core->processEvent(figureCurrentPosition);
	//		_core->processEvent(figureNewPosition);
	//		
	//		//Updating movesLog
	//		updateMovesLog();
	//	}
	//}
	//else {
	//	_core->clearData();
	//	Director::getInstance()->popToRootScene();

	//	return;
	//}

	//load.close();
	//_core->setLogMessage(LoadGameSuccessString + filename);
}

void NewGameLayer::processEvent(cocos2d::Vec2 location)
{
	Location boardLocation;

	float floatX = (location.y - BOARD_Y) / SQUARE_SIZE;
	if (floatX < 0 || floatX >= BOARD_SIZE) {
		return;
	}

	float floatY = (location.x - BOARD_X) / SQUARE_SIZE;
	if (floatY < 0 || floatY >= BOARD_SIZE) {
		return;
	}

	boardLocation.x = static_cast<int>(floatX);
	boardLocation.y = static_cast<int>(floatY);

	if (_core->processEvent(boardLocation)) {
		if (_core->getGameOver()) {
			this->pause();
			//>pauseEventListenersForTarget(this);
		}
		// Setting SideToMoveIcon
		setActiveIcon();

		//Updating movesLog
		auto lastMove = _core->getLastMove();
		std::string text = (lastMove[0] == 'W') ? WHITE_PL_STRING : BLACK_PL_STRING;
		text += lastMove.substr(2, 5) + '\t' + lastMove.substr(7, 5);
		updateMovesLog(text);
	}
}

void NewGameLayer::update(float deltaTime) {
	updateTimers();
	_logMessageLabel->setString(_core->getLogMessage());
	/*if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(CHESS_CLOCK.c_str(), false);
	}*/
	if (AudioEngine::getState(_layerMusicID) != AudioEngine::AudioState::PLAYING) {
		_layerMusicID = AudioEngine::play2d(CHESS_CLOCK, true, _core->getSoundsVolume());
	}
}

void NewGameLayer::updateTimers() {
	std::pair<double, double> duration = _core->getGameDuration();
	std::string timer;
	const int number1 = static_cast<int>(duration.first);
	const int number2 = static_cast<int>(duration.second);

	//setting first timer
	if (number1 / 60 < 10) {
		timer = "0";
	}
	timer += std::to_string(number1 / 60) + ':';
	if (number1 % 60 < 10) {
		timer += "0";
	}
	timer += std::to_string(number1 % 60);

	_p1Timer->setString(timer);

	//setting second timer
	timer = "";

	if (duration.second / 60 < 10) {
		timer = "0";
	}
	timer += std::to_string(number2 / 60) + ':';
	if (number2 % 60 < 10) {
		timer += "0";
	}
	timer += std::to_string(number2 % 60);

	_p2Timer->setString(timer);
}

void NewGameLayer::updateMovesLog(std::string lastMove)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto textWidget = ui::Text::create();
	if (textWidget) {
		textWidget->setString(lastMove);
		textWidget->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		textWidget->setFontName(FONT);
		(lastMove[0] == 'W') ? textWidget->setColor(METALLIC_GOLD) : textWidget->setColor(CHOKOLATE);

		float newLabelPosition = _playersMoves.back()->getPosition().y - LABEL_DISTANCE;
		float scrollViewInnerPosition = _scrollView->getInnerContainerPosition().y;
		//// Increasing innerContainer if needed
		if (newLabelPosition < 0) {
			float size = _scrollView->getInnerContainer()->getContentSize().height + winSize.height;
			_scrollView->setInnerContainerSize(Size(_scrollView->getInnerContainerSize().width, size));
			for (auto it = _playersMoves.begin(); it != _playersMoves.end(); ++it) {
				(*it)->setPosition(Vec2(labelCoordX, (*it)->getPosition().y + winSize.height));
			}
			newLabelPosition = _playersMoves.back()->getPosition().y - LABEL_DISTANCE;
			_scrollView->getInnerContainer()->setPositionY(scrollViewInnerPosition - winSize.height);
			scrollViewInnerPosition = _scrollView->getInnerContainerPosition().y;
		}
		//// Updating position for innerContainer if needed 
		if (newLabelPosition < scrollViewInnerPosition * (-1)) {
			_scrollView->getInnerContainer()->setPositionY(scrollViewInnerPosition + _scrollView->getContentSize().height - LABEL_DISTANCE);
		}

		textWidget->setPosition(Vec2(labelCoordX, _playersMoves.back()->getPosition().y - LABEL_DISTANCE));
		textWidget->setFontSize(LABEL_FONT_SIZE);
		_playersMoves.pushBack(textWidget);
		_scrollView->addChild(textWidget);
	}
}

void NewGameLayer::onMouseDown(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	processEvent(mouseEvent->getLocationInView());
}

void NewGameLayer::onSaveGameClick(cocos2d::Ref* sender)
{
	if (_core->getGameOver()) {
		_core->setLogMessage(ErrorSaveGameOverString);

		return;
	}
	this->pause();
	AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
	AudioEngine::stop(_layerMusicID);
	Director::getInstance()->pushScene(SaveGameScene::createScene());
}

void NewGameLayer::onLoadGameClick(cocos2d::Ref* sender)
{
	std::string SavedGamesDir = FileUtils::getInstance()->getWritablePath();
	SavedGamesDir += SAVED_GAMES_DIR;
	
	if (!fs::is_directory(SavedGamesDir) || fs::is_empty(SavedGamesDir)) {
		_core->setLogMessage(ErrorLoadGameString);

		return;
	}
	
	if (_core->getFigureToPromote()) {
		_core->setLogMessage(ErrorLoadDuringPromotionString);

		return;
	}

	this->pause();
	AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
	AudioEngine::stop(_layerMusicID);
	Director::getInstance()->pushScene(LoadGameScene::createScene());
}

void NewGameLayer::onGameSettingsClick(cocos2d::Ref* sender)
{
	this->pause();
	AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
	AudioEngine::stop(_layerMusicID);
	Director::getInstance()->pushScene(GameSettingsMenu::createScene());
}

void NewGameLayer::onQuitGameClick(cocos2d::Ref* sender)
{
	this->pause();
	AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
	AudioEngine::stop(_layerMusicID);
	Director::getInstance()->pushScene(QuitGameScene::createScene());
}

void NewGameLayer::setActiveIcon() {
	if (_core->getHalfTurn() % 2) {
		//this->on
		_whiteKingIcon->setSpriteFrame(WK_ACT_ICON);
		_blackKingIcon->setSpriteFrame(BK_PAS_ICON);
	}
	else {
		_whiteKingIcon->setSpriteFrame(WK_PAS_ICON);
		_blackKingIcon->setSpriteFrame(BK_ACT_ICON);
	}
}
