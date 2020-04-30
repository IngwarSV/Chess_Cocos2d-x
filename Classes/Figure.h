#pragma once

#include <string>
#include <vector>
#include "cocos2d.h"
#include "Specification.h"

using namespace DEF_SETT;

class Figure : public cocos2d::Sprite
{
protected:
	Color _color;
	Type _type;
	std::string _name{};
	Location _location;
	std::string _passiveStateFrameName;
	std::string _activeStateFrameName;

	std::vector<Location>* _possibleMoves = nullptr;

public:
	Figure(Color color, Location location, Type type);
	virtual ~Figure();
	// attributes
	bool _firstMove;

	// methods

	//// pure virtual method, returns vector of figure's possible moves, 
	//// considering situation on the board
	virtual std::vector<Location>* getPossibleMoves(Figure*** board);



	void onMouseDown(cocos2d::Event* event);



	////getters
	const Color getFigureColor() const;
	const Type getType() const;
	const std::string& getFigureName() const;
	const Location getLocation() const;

	////setters
	void setLocation(Location point);
	//void setLocation(Vec2 point);
	void setPassiveState();
	void setActiveState();
	
};

