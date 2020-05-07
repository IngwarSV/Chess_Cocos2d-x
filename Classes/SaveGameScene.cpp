#include "SaveGameScene.h"

using namespace cocos2d;
using namespace ui;
using namespace DEF_SETT;
namespace fs = std::filesystem;

cocos2d::Scene* SaveGameScene::createScene() {
	cocos2d::Scene* scene = cocos2d::Scene::create();
	auto layer = SaveGameScene::create();
	scene->addChild(layer);

	return scene;
}

bool SaveGameScene::init() {
	//
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	// Setting background
	auto background = cocos2d::Sprite::create("BG2HD.png");
	background->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(background, 0);

	auto box = cocos2d::Sprite::createWithSpriteFrameName("ScrollView.png");
	box->setAnchorPoint(Point::ANCHOR_MIDDLE);
	box->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(box, 1);

	
	
	//Adding ScrollView for movesLog (BUTTONS?????)
	_scrollView = cocos2d::ui::ScrollView::create();
	_scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	_scrollView->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_scrollView->setContentSize(SCROLL_VIEW_SIZE);
	_scrollView->setBackGroundColorType(ui::ScrollView::BackGroundColorType::NONE);
	_scrollView->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
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
	this->addChild(_scrollView, 2);

	std::string SavedGamesDir = FileUtils::getInstance()->getWritablePath();
	SavedGamesDir += SAVED_GAMES_DIR;
	if (!FileUtils::getInstance()->isDirectoryExist(SavedGamesDir)) {
		FileUtils::getInstance()->createDirectory(SavedGamesDir);
	}

	for (auto& files : fs::directory_iterator(SavedGamesDir)) {
		_exsistingFiles.pushBack(ui::Text::create());
		auto text = _exsistingFiles.back();
		text->setString(files.path().filename().string());
		text->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		text->setFontName(FONT);
		text->setFontSize(LABEL_FONT_SIZE * 2);
		text->setColor(METALLIC_GOLD);
		float coordY = _scrollView->getInnerContainerSize().height - LABEL_DISTANCE * (_exsistingFiles.size() - 1) * 2;
		text->setPosition(Vec2(labelCoordX, coordY));
		_scrollView->addChild(text, 3);
	}

	auto textField = TextField::create("Type fileName", FONT, LABEL_FONT_SIZE);
	textField->setPosition(Vec2(winSize.width / 2 - 300, winSize.height / 2));
	// make this TextField password enabled
	textField->setPasswordEnabled(true);

	// set the maximum number of characters the user can enter for this TextField
	textField->setMaxLength(10);
	textField->setCursorEnabled(true);

	/*textField->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		std::cout << "editing a TextField" << std::endl;
	});*/

	this->addChild(textField, 5);








	//Handle Touch Events
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(SaveGameScene::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void SaveGameScene::onMouseDown(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	bool promotionIsMade = false;

};
