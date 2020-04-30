#include "Units.h"
using namespace cocos2d;

F_King::F_King(Color color, Location location, Type type) : Figure(color, location, type)
{
}

F_King::~F_King() {
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);
	if (this->getParent())
	{
		this->getParent()->removeChild(this);
	}
}

std::vector<Location>* F_King::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves->clear();

	//"vertical" moves
	Location tempLocation = this->getLocation();
	tempLocation.x -= 1;

	if (tempLocation.x >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;

	if (tempLocation.x < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	//"horizontal" moves
	tempLocation = this->getLocation();
	tempLocation.y -= 1;

	if (tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.y += 1;

	if (tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	//right diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y += 1;

	if (tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y += 1;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	//left diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y -= 1;

	if (tempLocation.x >= 0 && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y -= 1;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	return _possibleMoves;
}


F_Queen::F_Queen(Color color, Location location, Type type) : Figure(color, location, type) {}

F_Queen::~F_Queen() {
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);
	if (this->getParent())
	{
		this->getParent()->removeChild(this);
	}
}

std::vector<Location>* F_Queen::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves->clear();

	//vertical moves
	Location tempLocation = this->getLocation();

	for (tempLocation.x += 1; tempLocation.x < BOARD_SIZE; ++tempLocation.x) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();

	for (tempLocation.x -= 1; tempLocation.x >= 0; --tempLocation.x) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//horizontal moves
	tempLocation = this->getLocation();

	for (tempLocation.y += 1; tempLocation.y < BOARD_SIZE; ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();

	for (tempLocation.y -= 1; tempLocation.y >= 0; --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//right diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y += 1;

	for (; tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE; --tempLocation.x, ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y += 1;

	for (; tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE; ++tempLocation.x, ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//left diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y -= 1;

	for (; tempLocation.x >= 0 && tempLocation.y >= 0; --tempLocation.x, --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y -= 1;

	for (; tempLocation.x < BOARD_SIZE && tempLocation.y >= 0; ++tempLocation.x, --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	return _possibleMoves;
}


F_Bishop::F_Bishop(Color color, Location location, Type type) : Figure(color, location, type) {}

F_Bishop::~F_Bishop() {
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);
	if (this->getParent())
	{
		this->getParent()->removeChild(this);
	}
}

std::vector<Location>* F_Bishop::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves->clear();

	//right diagonal moves
	Location tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y += 1;

	for (; tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE; --tempLocation.x, ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y += 1;

	for (; tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE; ++tempLocation.x, ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//left diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y -= 1;

	for (; tempLocation.x >= 0 && tempLocation.y >= 0; --tempLocation.x, --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y -= 1;

	for (; tempLocation.x < BOARD_SIZE && tempLocation.y >= 0; ++tempLocation.x, --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	return _possibleMoves;
}



F_Knight::F_Knight(Color color, Location location, Type type) : Figure(color, location, type) {}

F_Knight::~F_Knight() {
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);
	if (this->getParent())
	{
		this->getParent()->removeChild(this);
	}
}

std::vector<Location>* F_Knight::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves->clear();

	//"vertical" up moves
	Location tempLocation = this->getLocation();
	tempLocation.x -= 2;
	tempLocation.y -= 1;

	if (tempLocation.x >= 0 && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x -= 2;
	tempLocation.y += 1;

	if (tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	//"vertical" down moves
	tempLocation = this->getLocation();
	tempLocation.x += 2;
	tempLocation.y -= 1;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 2;
	tempLocation.y += 1;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	//"horizontal" left moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y -= 2;

	if (tempLocation.x >= 0 && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y -= 2;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	//"horizontal" right moves
	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y += 2;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y += 2;

	if (tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	return _possibleMoves;
}


F_Rook::F_Rook(Color color, Location location, Type type) : Figure(color, location, type) {}

F_Rook::~F_Rook() {
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);
	if (this->getParent())
	{
		this->getParent()->removeChild(this);
	}
}

std::vector<Location>* F_Rook::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves->clear();

	//vertical moves
	Location tempLocation = this->getLocation();

	for (tempLocation.x += 1; tempLocation.x < BOARD_SIZE; ++tempLocation.x) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();

	for (tempLocation.x -= 1; tempLocation.x >= 0; --tempLocation.x) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//horizontal moves
	tempLocation = this->getLocation();

	for (tempLocation.y += 1; tempLocation.y < BOARD_SIZE; ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();

	for (tempLocation.y -= 1; tempLocation.y >= 0; --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves->push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	return _possibleMoves;
}



F_Pawn::F_Pawn(Color color, Location location, Type type) : Figure(color, location, type) {}

F_Pawn::~F_Pawn() {
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);
	if (this->getParent())
	{
		this->getParent()->removeChild(this);
	}
}

std::vector<Location>* F_Pawn::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves->clear();

	int delta = (this->getFigureColor() == Color::WHITE) ? 1 : -1;
	
	//Moves
	Location tempLocation = this->getLocation();
	tempLocation.x += delta;

	if (tempLocation.x >= 0 && tempLocation.x < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves->push_back(tempLocation);
		}
	}

	if (this->_firstMove) {
		const Figure* figure1 = board[tempLocation.x][tempLocation.y];

		tempLocation.x += delta;
		if (tempLocation.x >= 0 && tempLocation.x < BOARD_SIZE) {
			const Figure* figure2 = board[tempLocation.x][tempLocation.y];

			if (!figure1 && !figure2) {
				_possibleMoves->push_back(tempLocation);
			}
		}
	}

	//Attacks
	tempLocation = this->getLocation();
	tempLocation.x += delta;
	tempLocation.y += delta;

	if (tempLocation.x >= 0 && tempLocation.x < BOARD_SIZE &&
		tempLocation.y >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (figure) {
			if (figure->getFigureColor() != this->getFigureColor()) {
				_possibleMoves->push_back(tempLocation);
			}
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += delta;
	tempLocation.y -= delta;

	if (tempLocation.x >= 0 && tempLocation.x < BOARD_SIZE &&
		tempLocation.y >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (figure) {
			if (figure->getFigureColor() != this->getFigureColor()) {
				_possibleMoves->push_back(tempLocation);
			}
		}
	}

	return _possibleMoves;
}
