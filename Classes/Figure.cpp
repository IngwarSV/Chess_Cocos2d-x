#include "Figure.h"

using namespace cocos2d;

Figure::Figure(Color color, Location location, Type type)
{
	
	this->_color = color;
	this->_type = type;
	this->_name += static_cast<char>(color);
	this->_name += static_cast<char>(type);
	this->_location = location;
	this->_firstMove = true;
	this->_possibleMoves = new std::vector<Location>();
	this->_passiveStateFrameName = _name + "_Pas.png";
	this->_activeStateFrameName = _name + "_Act.png";
	this->initWithSpriteFrameName(_passiveStateFrameName);
	this->setAnchorPoint(Vec2(0.0, 0.0));
	this->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE), 
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
}

Figure::~Figure()
{
	
	delete _possibleMoves;
}

std::vector<Location>* Figure::getPossibleMoves(Figure*** board)
{
	return nullptr;
}

//void Figure::onMouseDown(cocos2d::Event* event)
//{
//	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
//
//	Vec2 globalLocation = mouseEvent->getLocationInView();
//
//	this->getParent()->setUserData(this);
//	//this->getParent()->setUserObject(this);
//
//
//}

const Color Figure::getFigureColor() const
{
	return _color;
}

const Type Figure::getType() const
{
	return _type;
}

const std::string& Figure::getFigureName() const
{
	return _name;
}

const Location Figure::getLocation() const
{
	return _location;
}

void Figure::setLocation(Location point)
{
	_location.x = point.x;
	_location.y = point.y;
}

//void Figure::setLocation(Vec2 point)
//{
//	static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
//		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE)
//}

void Figure::setPassiveState()
{
	this->setSpriteFrame(_passiveStateFrameName);


}

void Figure::setActiveState()
{
	this->setSpriteFrame(_activeStateFrameName);
}

