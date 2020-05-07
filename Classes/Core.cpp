#include "Core.h"

using namespace cocos2d;
using namespace std::chrono;

static bool s_firstRun = true;
static Core s_sharedCore;

void Core::initialSetup()
{
	// Creating armies with figures 

	//// White Army
	_WKing = new F_King(Color::WHITE, WK_INIT_POS);
	_whiteArmy.pushBack(_WKing);
	_whiteArmy.pushBack(new F_Queen(Color::WHITE, WQ_INIT_POS));
	_whiteArmy.pushBack(new F_Bishop(Color::WHITE, WB_INIT_POS1));
	_whiteArmy.pushBack(new F_Bishop(Color::WHITE, WB_INIT_POS2));
	_whiteArmy.pushBack(new F_Knight(Color::WHITE, WN_INIT_POS1));
	_whiteArmy.pushBack(new F_Knight(Color::WHITE, WN_INIT_POS2));
	_whiteArmy.pushBack(new F_Rook(Color::WHITE, WR_INIT_POS1));
	_whiteArmy.pushBack(new F_Rook(Color::WHITE, WR_INIT_POS2));

	//// Black Army
	_BKing = new F_King(Color::BLACK, BK_INIT_POS);
	_blackArmy.pushBack(_BKing);
	_blackArmy.pushBack(new F_Queen(Color::BLACK, BQ_INIT_POS));
	_blackArmy.pushBack(new F_Bishop(Color::BLACK, BB_INIT_POS1));
	_blackArmy.pushBack(new F_Bishop(Color::BLACK, BB_INIT_POS2));
	_blackArmy.pushBack(new F_Knight(Color::BLACK, BN_INIT_POS1));
	_blackArmy.pushBack(new F_Knight(Color::BLACK, BN_INIT_POS2));
	_blackArmy.pushBack(new F_Rook(Color::BLACK, BR_INIT_POS1));
	_blackArmy.pushBack(new F_Rook(Color::BLACK, BR_INIT_POS2));

	// Pawns
	_pawnQuantity = PAWN_QUANTITY;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		Location tempWhite = WP_INIT_POS1;
		Location tempBlack = BP_INIT_POS1;
		tempWhite.y += i;
		tempBlack.y += i;

		_whiteArmy.pushBack(new F_Pawn(Color::WHITE, tempWhite));
		_blackArmy.pushBack(new F_Pawn(Color::BLACK, tempBlack));
	}

	// updating board's situation considering figures' positions
	for (auto figure : _whiteArmy) {
		Location location = figure->getLocation();

		_board[location.x][location.y] = figure;
	}

	for (Figure* figure : _blackArmy) {
		Location location = figure->getLocation();

		_board[location.x][location.y] = figure;
	}

	// initializing rest of the attributes
	_currentArmy = &_whiteArmy;
	_enemyArmy = &_blackArmy;
	_activeKing = _WKing;



	_figureToMove = nullptr;
	// for "en passant" actions 
	_enPassantFigure = nullptr; // pawn that just made two-squares move
	//_firstEnPassantPoint = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

	//// for "promotion" actions 
	_figureToPromote = nullptr;
	//_promotedFigPreviousLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
	_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
	_halfTurn = 1;
	_CHECK = false;
	_gameOver = false;

	_turnDuration = time(NULL);
	_p1GameDuration = 0.0;
	_p2GameDuration = 0.0;
	

	_logMessage = NewGameString;
}


bool Core::init() {
	// creating Board[8][8]
	this->_board = new Figure * *[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; ++i) {
		_board[i] = new Figure * [BOARD_SIZE];
	}

	//Setting board with nullptrs
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			_board[i][j] = nullptr;
		}
	}

	auto spritecache = SpriteFrameCache::getInstance();

	spritecache->addSpriteFramesWithFile("GameImages.plist");

	return true;
}


Core* Core::sharedCore()
{
	if (s_firstRun) {
		s_sharedCore.init();
		s_firstRun = false;
	}
	return &s_sharedCore;
}



bool Core::processEvent(Location newLocation)
{
	// ending promotion action (if use shared ptrs - it is possible to draw pawn till now)
	if (_figureToPromote) {
		_figureToMove = _figureToPromote;
		_figureToPromote = nullptr;

		// deleting data for En passant
		_enPassantFigure = nullptr;

		return endTurn(_tempLocation, _figureToMove->getLocation());;
	}

	//chosing figureToMove
	Figure* newFigureToMove = _board[newLocation.x][newLocation.y];

	if (_currentArmy->contains(newFigureToMove)) {
		if (_figureToMove) {
			_figureToMove->setPassiveState();
		}
		//setting previous figureToMove in inActive state
		_figureToMove = newFigureToMove;
		_figureToMove->setActiveState();

		return false;
	}

	if (!_figureToMove) {
		return false;
	}

	Location currentLocation = _figureToMove->getLocation();


	//castling checking, execution if true
	if (castling(_figureToMove, currentLocation, newLocation)) {
		// rook movement
		Location rookPosition;
		Location rookNewPosition;
		std::string notation;

		if (newLocation.y > currentLocation.y) {
			rookPosition = Location{ currentLocation.x, BOARD_SIZE - 1 };
			rookNewPosition = Location{ currentLocation.x, newLocation.y - 1 };
			notation = CastlingShort;
		}
		else {
			rookPosition = Location{ currentLocation.x, 0 };
			rookNewPosition = Location{ currentLocation.x, newLocation.y + 1 };
			notation = CastlingLong;
		}
		Figure* rook = _board[rookPosition.x][rookPosition.y];

		_board[rookPosition.x][rookPosition.y] = nullptr;
		_board[rookNewPosition.x][rookNewPosition.y] = rook;
		rook->setLocation(rookNewPosition);
		rook->_firstMove = false;
		rook->runAction(MoveTo::create(0.1f, convertCoord(rookNewPosition)));

		// deleting data for En passant
		_enPassantFigure = nullptr;
		_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
		
		//Updating logMessage
		_logMessage = CastlingPerfomed + notation;

		makeMove(_figureToMove, currentLocation, newLocation);

		return endTurn(currentLocation, newLocation);
	}


	// en passant checking, execution if true
	if (enPassant(_figureToMove, currentLocation, newLocation)) {
		Location secondEnPassantPoint = _enPassantFigure->getLocation();

		deletingFigure(_enPassantFigure);
		_board[secondEnPassantPoint.x][secondEnPassantPoint.y] = nullptr;
		

		// deleting data for En passant
		_enPassantFigure = nullptr;
		_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
		
		//Updating logMessage
		_logMessage = EnPassantPerformedString + getMoveString(currentLocation, newLocation);;
		
		makeMove(_figureToMove, currentLocation, newLocation);

		return endTurn(currentLocation, newLocation);
	}


	// checking if figureToMove can execute command
	bool moveIsLegal = false;
	auto v_possibleMoves = _figureToMove->getPossibleMoves(_board);

	for (auto possiblePosition : *v_possibleMoves) {
		if (newLocation == possiblePosition) {
			moveIsLegal = true;

			break;
		}
	}

	if (!moveIsLegal) {
		_logMessage = ErrorMoveIsIllegal + getMoveString(currentLocation, newLocation);

		return false;
	}
		

	// checking if figure's movement doesn't endanger the king
	if (isKingInDanger(_figureToMove, currentLocation, newLocation)) {
		_logMessage = ErrorKingIsInDanger + getMoveString(currentLocation, newLocation);

		return false;
	}

	// deleting data for En passant
	_enPassantFigure = nullptr;
	_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

	//checking for new En passant data
	if (_figureToMove->_firstMove) {
		if (_figureToMove->getType() == Type::PAWN) {
			int delta = newLocation.x - currentLocation.x;

			if (delta == 2) {
				_enPassantFigure = _figureToMove;
				_tempLocation = Location{ newLocation.x - 1, newLocation.y };
			}
			else if (delta == -2) {
				_enPassantFigure = _figureToMove;
				_tempLocation = Location{ newLocation.x + 1, newLocation.y };
			}
		}
	}

	// Removing enemy's figure (if needed) and moving figure on new position
	Figure* enemyFigure = _board[newLocation.x][newLocation.y];
	if (enemyFigure) {
		deletingFigure(enemyFigure);
	}

	//Updating logMessage
	_logMessage = PreviousMoveString + getMoveString(currentLocation, newLocation);
	

	// Checking for promotion
	if (_figureToMove->getType() == Type::PAWN && (newLocation.x == 0 || newLocation.x == BOARD_SIZE - 1)) {
		// Starting promotion action
		arrangePromotion(_figureToMove);
		_tempLocation = currentLocation;
		_figureToPromote = _figureToMove;
		
		makeMove(_figureToMove, currentLocation, newLocation);
		
		return false;
	}

	// Ending move
	makeMove(_figureToMove, currentLocation, newLocation);

	return endTurn(currentLocation, newLocation);
}


bool Core::castling(Figure* king, Location currentLocation, Location newLocation)
{
	if ((king->getType() == Type::KING) && !_CHECK) {
		if (king->_firstMove) {
			if (newLocation == Location{ king->getLocation().x, 2 } ||
				newLocation == Location{ king->getLocation().x, 6 }) {

				// cheking if squares king has to move are empty
				int delta = (newLocation.y - currentLocation.y) / 2;
				Location square1{ currentLocation.x, currentLocation.y + delta };
				Location square2{ currentLocation.x, currentLocation.y + delta + delta };
				if (!_board[currentLocation.x][square1.y] && !_board[currentLocation.x][square2.y]) {

					// cheking if squares king to move are not under attack
					if (!isKingInDanger(king, currentLocation, square1) && !isKingInDanger(king, currentLocation, square2)) {

						// choosing kingside or queenside rook
						Figure* rook = nullptr;
						if (delta > 0) {
							rook = _board[currentLocation.x][BOARD_SIZE - 1];
						}
						else {
							rook = _board[currentLocation.x][0];
							// cheking if square queenside rook has to move is empty
							if (_board[currentLocation.x][1]) {
								return false;
							}
						}

						// cheking rook
						if (rook && rook->getType() == Type::ROOK && rook->_firstMove) {
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool Core::enPassant(Figure* figureToMove, Location currentLocation, Location newLocation)
{
	bool moveIsPossible = false;

	if (figureToMove->getType() == Type::PAWN && _enPassantFigure) {
		if (newLocation == _tempLocation) {
			// location of the pawn, that just made two-squares move
			Location secondEnPassantPoint = _enPassantFigure->getLocation();
			int delta = currentLocation.y - secondEnPassantPoint.y;

			if (currentLocation.x == secondEnPassantPoint.x && (delta == 1 || delta == -1)) {
				// setting board as if move's been executed
				_enemyArmy->eraseObject(_enPassantFigure);
				_board[currentLocation.x][currentLocation.y] = nullptr;
				_board[secondEnPassantPoint.x][secondEnPassantPoint.y] = nullptr;
				_board[newLocation.x][newLocation.y] = figureToMove;
				figureToMove->setLocation(newLocation);

				// checking for "check"
				moveIsPossible = !isCheck();

				// setting board to previous position
				_enemyArmy->pushBack(_enPassantFigure);
				_board[currentLocation.x][currentLocation.y] = figureToMove;
				_board[secondEnPassantPoint.x][secondEnPassantPoint.y] = _enPassantFigure;
				_board[newLocation.x][newLocation.y] = nullptr;
				figureToMove->setLocation(currentLocation);
			}
		}
	}

	return moveIsPossible;
}

bool Core::isKingInDanger(Figure* figureToMove, Location currentLocation, Location newLocation)
{
	Figure* enemyFigure = _board[newLocation.x][newLocation.y];
	if (enemyFigure) {
		//enemyFigure->retain(); //????????
		_enemyArmy->eraseObject(enemyFigure);
	}

	// setting board as if move's been executed
	_board[currentLocation.x][currentLocation.y] = nullptr;
	_board[newLocation.x][newLocation.y] = figureToMove;
	figureToMove->setLocation(newLocation);

	// checking for "check"
	bool inDanger = isCheck();

	// setting board to previous position
	_board[currentLocation.x][currentLocation.y] = figureToMove;
	_board[newLocation.x][newLocation.y] = enemyFigure;
	figureToMove->setLocation(currentLocation);

	if (enemyFigure) {
		_enemyArmy->pushBack(enemyFigure);
	}

	return inDanger;
}

void Core::arrangePromotion(Figure* figureToMove)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto figureParent = figureToMove->getParent();
	if (!figureParent) {
		return;
	}
	// pausing all actions, listeners, lowering opacity of total gameLayer
	figureParent->pause();
	for (auto child : figureParent->getChildren()) {
		child->setOpacity(100);
	}

	// Creating QueenSprite
	auto queen = Sprite::createWithSpriteFrameName(GOLDEN_Q_ICON);
	queen->setScale(0.8f);
	queen->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	queen->setPosition(winSize.width / 2, winSize.height / 2 + 50);
	figureParent->addChild(queen, 100, "Q");
	// Creating RookSprite
	auto rook = Sprite::createWithSpriteFrameName(GOLDEN_R_ICON);
	rook->setScale(0.8f);
	rook->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	rook->setPosition(winSize.width / 2 + 100, winSize.height / 2);
	figureParent->addChild(rook, 100, "R");
	//Creating KnightSprite
	auto knight = Sprite::createWithSpriteFrameName(GOLDEN_H_ICON);
	knight->setScale(0.8f);
	knight->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	knight->setPosition(winSize.width / 2 - 100, winSize.height / 2);
	figureParent->addChild(knight, 100, "N");
	// Creating BishopSprite
	auto bishop = Sprite::createWithSpriteFrameName(GOLDEN_B_ICON);
	bishop->setScale(0.8f);
	bishop->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	bishop->setPosition(winSize.width / 2, winSize.height / 2 - 50);
	figureParent->addChild(bishop, 100, "B");

	// Creating EventListeners for promotion choice
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [&](Event* event) {
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		auto figureParent = _activeKing->getParent();
		
		auto queen = figureParent->getChildByName("Q");
		auto rook = figureParent->getChildByName("R");
		auto knight = figureParent->getChildByName("N");
		auto bishop = figureParent->getChildByName("B");

		bool promotionIsMade = false;
		//Checking for "Queen" choice
		if (queen && queen->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			executePromotion(_figureToPromote, Type::QUEEN);
			promotionIsMade = true;
		}
		//Checking for "Rook" choice
		else if (rook && rook->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			executePromotion(_figureToPromote, Type::ROOK);
			promotionIsMade = true;
		}
		//Checking for "Knight" choice
		else if (knight && knight->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			executePromotion(_figureToPromote, Type::KNIGHT);
			promotionIsMade = true;
		}
		//Checking for "Bishop" choice
		else if (bishop && bishop->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			executePromotion(_figureToPromote, Type::BISHOP);
			promotionIsMade = true;
		}

		if (promotionIsMade) {
			figureParent->removeChild(figureParent->getChildByName("Q"));
			figureParent->removeChild(figureParent->getChildByName("R"));
			figureParent->removeChild(figureParent->getChildByName("N"));
			figureParent->removeChild(figureParent->getChildByName("B"));
			figureParent->resume();
			for (auto child : figureParent->getChildren()) {
				child->setOpacity(255);
			}
			figureParent->getEventDispatcher()->dispatchEvent(event);
		}
	};

	figureParent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, figureParent);
}

void Core::executePromotion(Figure* figureToMove, Type figureType)
{
	Color color = figureToMove->getFigureColor();
	Location newPosition = figureToMove->getLocation();
	Figure* promotedFigure = nullptr;
	std::bitset<BOARD_SIZE>* bit_currentArmy;
	bit_currentArmy = (_halfTurn % 2) ? &_bit_whiteArmy : &_bit_blackArmy;
	_logMessage = ChoosePromotionString;
	auto figureParent = figureToMove->getParent();
	if (!figureParent) {
		return;
	}
	
	
	if (figureType == Type::QUEEN) {
		promotedFigure = new F_Queen(color, newPosition);

		(bit_currentArmy->test(bit_F_Queen1)) ?
			bit_currentArmy->set(bit_F_Queen2) : bit_currentArmy->set(bit_F_Queen1);
	}
	else if (figureType == Type::BISHOP) {
		promotedFigure = new F_Bishop(color, newPosition);

		((newPosition.x + newPosition.y) % 2) ?
			bit_currentArmy->set(bit_F_Bishop1) : bit_currentArmy->set(bit_F_Bishop2);
	}
	else if (figureType == Type::KNIGHT) {
		promotedFigure = new F_Knight(color, newPosition);

		(bit_currentArmy->test(bit_F_Knight1)) ?
			bit_currentArmy->set(bit_F_Knight2) : bit_currentArmy->set(bit_F_Knight1);
	}
	else if (figureType == Type::ROOK) {
		promotedFigure = new F_Rook(color, newPosition);

		(bit_currentArmy->test(bit_F_Rook1)) ?
			bit_currentArmy->set(bit_F_Rook2) : bit_currentArmy->set(bit_F_Rook1);
	}

	// deleting pawn
	deletingFigure(figureToMove);

	// setting new figure
	_board[newPosition.x][newPosition.y] = promotedFigure;
	_currentArmy->pushBack(promotedFigure);
	promotedFigure->setPosition(convertCoord(newPosition));
	figureParent->addChild(promotedFigure, BOARD_SIZE - newPosition.x);
	_figureToPromote = promotedFigure;

	_logMessage = PromotionSuccessString;
}

bool Core::isCheck()
{
	Location kingPosition = _activeKing->getLocation();

	for (auto enemyFigure : *_enemyArmy) {
		auto v_possibleMoves = enemyFigure->getPossibleMoves(_board);

		for (auto possiblePosition : *v_possibleMoves) {
			if (kingPosition == possiblePosition) {
				return true;
			}
		}
	}

	return false;
}

bool Core::isCheckmate()
{
	Location kingLocation = _activeKing->getLocation();

	// checking if king can escape check by himself
	auto v_possibleMoves = _activeKing->getPossibleMoves(_board);

	for (auto possiblePosition : *v_possibleMoves) {
		if (!isKingInDanger(_activeKing, kingLocation, possiblePosition)) {
			_logMessage += WarningCheckString;

			return false;
		}
	}

	// checking if army can protect their king 
	// (test using king's moves is repeating, but mostly this second check won't be performed)

	for (auto figure : *_currentArmy) {
		auto v_possibleMoves = figure->getPossibleMoves(_board);
		Location figureLocation = figure->getLocation();

		for (auto possiblePosition : *v_possibleMoves) {
			if (!isKingInDanger(figure, figureLocation, possiblePosition)) {
				_logMessage += WarningCheckString;

				return false;
			}
		}

		//// checking if enPassant can be performed to protect the king
		if (figure->getType() == Type::PAWN && _enPassantFigure) {
			if (enPassant(figure, figure->getLocation(), _tempLocation)) {
				_logMessage += WarningCheckString;

				return false;
			}
		}
	}

	// Game Over
	_logMessage += WarningCheckmateString;

	return true;
}

bool Core::isDraw()
{
	// checking stalemate
	bool hasLegalMove = false;

	for (auto figure : *_currentArmy) {
		auto v_possibleMoves = figure->getPossibleMoves(_board);
		Location figureLocation = figure->getLocation();

		for (auto possiblePosition : *v_possibleMoves) {
			if (!isKingInDanger(figure, figureLocation, possiblePosition)) {
				hasLegalMove = true;

				break;
			}
		}

		// checking for enPassant move
		if (figure->getType() == Type::PAWN && _enPassantFigure && !hasLegalMove) {
			if (enPassant(figure, figure->getLocation(), _tempLocation)) {
				hasLegalMove = true;

				break;
			}
		}
	}

	if (!hasLegalMove) {
		//_logMessage = DrawStalemateString;

		return true;
	}

	// checking impossibility of checkmate
	std::bitset<BOARD_SIZE> _bit_temp = _bit_whiteArmy | _bit_blackArmy;

	//// cheking for pawns
	if (_pawnQuantity > 0) {
		return false;
	}

	//// two kings left (there is no bit for kings in the bitsets)
	if (!_bit_temp.to_ulong()) {
		//_logMessage = impossibleCheckmate1;

		return true;
	}

	//// king with/without bishop versus king and bishop(bishops) on the same color
	if (_bit_temp.to_ulong() == 4Ul || _bit_temp.to_ulong() == 8Ul) {
		//_logMessage = impossibleCheckmate2;

		return true;
	}

	//// king and knight versus king
	if (_bit_temp.to_ulong() == 1Ul && _bit_whiteArmy != _bit_blackArmy) {
		//_logMessage = impossibleCheckmate3;

		return true;
	}

	return false;
}

void Core::deletingFigure(Figure* enemyFigure)
{
	Type type = enemyFigure->getType();
	Location location = enemyFigure->getLocation();
	std::bitset<BOARD_SIZE>* bit_enemyArmy;

	bit_enemyArmy = (enemyFigure->getFigureColor() == Color::BLACK) ?
		&_bit_blackArmy : &_bit_whiteArmy;

	// updating bitset considering type of deleted figure
	switch (type) {

	case Type::QUEEN:
		(bit_enemyArmy->test(bit_F_Queen2)) ?
			bit_enemyArmy->reset(bit_F_Queen2) : bit_enemyArmy->reset(bit_F_Queen1);

		break;

	case Type::BISHOP:
		((location.x + location.y) % 2) ?
			bit_enemyArmy->reset(bit_F_Bishop1) : bit_enemyArmy->reset(bit_F_Bishop2);

		break;

	case Type::KNIGHT:
		(bit_enemyArmy->test(bit_F_Knight2)) ?
			bit_enemyArmy->reset(bit_F_Knight2) : bit_enemyArmy->reset(bit_F_Knight1);

		break;

	case Type::ROOK:
		(bit_enemyArmy->test(bit_F_Rook2)) ?
			bit_enemyArmy->reset(bit_F_Rook2) : bit_enemyArmy->reset(bit_F_Rook1);

		break;

	case Type::PAWN:
		_pawnQuantity -= 1;

		break;

	default:
		break;
	}

	_board[location.x][location.y] = nullptr;
	enemyFigure->getParent()->removeChild(enemyFigure);
	(enemyFigure->getFigureColor() == Color::BLACK) ?
		_blackArmy.eraseObject(enemyFigure) : _whiteArmy.eraseObject(enemyFigure);
	delete enemyFigure;
}

Vec2 Core::convertCoord(Location location)
{
	return Vec2(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
}

std::string Core::getMoveString(Location currentLocation, Location newLocation)
{
	std::string moveString;
	moveString = static_cast<char>(currentLocation.y) + 'A';
	moveString += static_cast<char>(currentLocation.x) + '1';
	moveString += '-';
	moveString += static_cast<char>(newLocation.y) + 'A';
	moveString += static_cast<char>(newLocation.x) + '1';

	return moveString;
}

void Core::clearData()
{
	// resetting armies' bitsets and pawn quantity
	_bit_whiteArmy.reset();
	_bit_blackArmy.reset();
	_pawnQuantity = 0;

	// deleting current figures
	for (auto figure : _whiteArmy) {
		figure->getParent()->removeChild(figure);
		delete figure;
	}
	_whiteArmy.clear();

	for (auto figure : _blackArmy) {
		figure->getParent()->removeChild(figure);
		delete figure;
	}
	_blackArmy.clear();

	// Setting board with nullptrs
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			_board[i][j] = nullptr;
		}
	}

	_currentArmy = nullptr;
	_enemyArmy = nullptr;
	_activeKing = nullptr;

	_figureToMove = nullptr;
	_enPassantFigure = nullptr;
	_figureToPromote = nullptr;
	_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE };
	_halfTurn = 1;
	_CHECK = false;
	_gameOver = false;

	_turnDuration = 0;
	_p1GameDuration = 0.0;
	_p2GameDuration = 0.0;

	_logMessage = "";





}

void Core::makeMove(Figure* figureToMove, Location currentLocation, Location newLocation) {
	_board[currentLocation.x][currentLocation.y] = nullptr;
	_board[newLocation.x][newLocation.y] = figureToMove;
	figureToMove->setLocation(newLocation);
	figureToMove->_firstMove = false;
	figureToMove->runAction(MoveTo::create(0.1f, convertCoord(newLocation)));
	figureToMove->setLocalZOrder(BOARD_SIZE - newLocation.x);
	figureToMove->setPassiveState();
	
}

bool Core::endTurn(Location currentLocation, Location newLocation)
{
	std::string moveString = _figureToMove->getFigureName() + getMoveString(currentLocation, newLocation);
	_figureToMove = nullptr;
	_halfTurn += 1;
	_CHECK = false;
	//_promotedFigPreviousLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
	
	// updating pointers for quick access
	const auto tempTime = time(NULL);
	
	if (_halfTurn % 2) {
		_currentArmy = &_whiteArmy;
		_enemyArmy = &_blackArmy;
		_activeKing = _WKing;
		_p2GameDuration += difftime(tempTime, _turnDuration);
	}
	else {
		_currentArmy = &_blackArmy;
		_enemyArmy = &_whiteArmy;
		_activeKing = _BKing;
		_p2GameDuration += difftime(tempTime, _turnDuration);
	}

	// Saving moveString
	const int duration = static_cast<int>(_p1GameDuration + _p2GameDuration);
	if (duration / 60 < 10) {
		moveString += "0";
	}
	moveString += std::to_string(duration / 60) + ':';
	if (duration % 60 < 10) {
		moveString += "0";
	}
	moveString += std::to_string(duration % 60);
	_movesVector.push_back(moveString);

	_turnDuration = tempTime;
	
	if (isCheck()) {
		_CHECK = true;
		if (isCheckmate()) {
			_gameOver = true;
		}
	}
	else if (isDraw()) {
		_gameOver = true;
	}

	return true;
}

void Core::loadGameDataString(std::string dataString) // create new custom Game from string, for testing
{
	std::istringstream load(dataString);

	// deleting existing game data to load saved game
	clearData();

	// loading _halfTurn
	load >> _halfTurn;

	// loading "en passant" actions 
	//// location of the pawn, that just made two squares move
	Location secondEnPassantPoint;
	load >> secondEnPassantPoint.x >> secondEnPassantPoint.y;
	//// _firstEnPassantPoint - square that was skipped by the pawn
	load >> _tempLocation.x >> _tempLocation.y;

	//parsing strings into figure's data
	std::string col_type_loc;

	while (load) {
		load >> col_type_loc;
		parseFigureDataString(col_type_loc);
	}

	// setting pointers for quick access
	if (_halfTurn % 2) {
		_currentArmy = &_whiteArmy;
		_enemyArmy = &_blackArmy;
		_activeKing = _WKing;
	}
	else {
		_currentArmy = &_blackArmy;
		_enemyArmy = &_whiteArmy;
		_activeKing = _BKing;
	}

	//// setting pointer to the pawn, that has just made two-squares move (or nullprt)
	_enPassantFigure = (secondEnPassantPoint != Location{ BOARD_SIZE, BOARD_SIZE }) ?
		_board[secondEnPassantPoint.x][secondEnPassantPoint.y] : nullptr;

	_CHECK = isCheck();
}

void Core::startTurnDurationCount()
{
	_turnDuration = time(NULL);
}

void Core::parseFigureDataString(std::string col_type_loc)
{
	Location location;
	Figure* newFigure = nullptr;
	Color color;

	//setting location, e.g "A8" == Location(0,0),"B3" == Location(5,1)
	location.x = static_cast<int>(col_type_loc[3] - '1');
	location.y = static_cast<int>(col_type_loc[2] - 'A');

	if (location.x < 0 || location.y < 0 || location.x > BOARD_SIZE - 1 || location.y > BOARD_SIZE - 1) {
		/*_logMessage = EnteringCustomString + ErrorLocCustomString +
			col_type_loc.substr(2, 2) + L'\n';*/
		return;
	}
	else if (_board[location.x][location.y]) {
		/*_logMessage = EnteringCustomString + ErrorLocOccupiedCustomString +
			col_type_loc.substr(2, 2) + L'\n';*/
		return;
	}

	//setting color
	if (col_type_loc[0] == static_cast<char>(Color::WHITE)) {
		color = Color::WHITE;

		//setting type, creating new figure, adding figure to white army and setting army's bitset
		switch (col_type_loc[1]) {

			case static_cast<char>(Type::KING) :
				newFigure = new F_King(color, location);
				_whiteArmy.pushBack(newFigure);
				_WKing = newFigure;

				break;

				case static_cast<char>(Type::QUEEN) :
					newFigure = new F_Queen(color, location);
					_whiteArmy.pushBack(newFigure);

					(_bit_whiteArmy.test(bit_F_Queen1)) ?
						_bit_whiteArmy.set(bit_F_Queen2) : _bit_whiteArmy.set(bit_F_Queen1);

					break;

					case static_cast<char>(Type::BISHOP) :
						newFigure = new F_Bishop(color, location);
						_whiteArmy.pushBack(newFigure);

						((location.x + location.y) % 2) ?
							_bit_whiteArmy.set(bit_F_Bishop1) : _bit_whiteArmy.set(bit_F_Bishop2);

						break;

						case static_cast<char>(Type::KNIGHT) :
							newFigure = new F_Knight(color, location);
							_whiteArmy.pushBack(newFigure);

							(_bit_whiteArmy.test(bit_F_Knight1)) ?
								_bit_whiteArmy.set(bit_F_Knight2) : _bit_whiteArmy.set(bit_F_Knight1);

							break;

							case static_cast<char>(Type::ROOK) :
								newFigure = new F_Rook(color, location);
								_whiteArmy.pushBack(newFigure);

								(_bit_whiteArmy.test(bit_F_Rook1)) ?
									_bit_whiteArmy.set(bit_F_Rook2) : _bit_whiteArmy.set(bit_F_Rook1);

								break;

								case static_cast<char>(Type::PAWN) :
									newFigure = new F_Pawn(color, location);
									_whiteArmy.pushBack(newFigure);
									_pawnQuantity += 1;

									break;

								default:
									/*_logMessage = EnteringCustomString + ErrorTypeCustomString +
										col_type_loc.substr(0, 2) + L'\n';*/

									return;
		}

		//setting first move state
		if (col_type_loc[4] != L'1') {
			newFigure->_firstMove = false;
		}

		_board[location.x][location.y] = newFigure;

		/*_logMessage = EnteringCustomString + FigureIsPlacedString +
			col_type_loc.substr(0, 4) + L'\n';*/

		return;
	}
	else if (col_type_loc[0] == static_cast<char>(Color::BLACK)) {
		color = Color::BLACK;

		//setting type, creating new figure, adding figure to black army and setting army's bitset
		switch (col_type_loc[1]) {

			case static_cast<char>(Type::KING) :
				newFigure = new F_King(color, location);
				_blackArmy.pushBack(newFigure);
				_BKing = newFigure;

				break;

				case static_cast<char>(Type::QUEEN) :
					newFigure = new F_Queen(color, location);
					_blackArmy.pushBack(newFigure);

					(_bit_blackArmy.test(bit_F_Queen1)) ?
						_bit_blackArmy.set(bit_F_Queen2) : _bit_blackArmy.set(bit_F_Queen1);

					break;

					case static_cast<char>(Type::BISHOP) :
						newFigure = new F_Bishop(color, location);
						_blackArmy.pushBack(newFigure);

						((location.x + location.y) % 2) ?
							_bit_blackArmy.set(bit_F_Bishop1) : _bit_blackArmy.set(bit_F_Bishop2);

						break;

						case static_cast<char>(Type::KNIGHT) :
							newFigure = new F_Knight(color, location);
							_blackArmy.pushBack(newFigure);

							(_bit_blackArmy.test(bit_F_Knight1)) ?
								_bit_blackArmy.set(bit_F_Knight2) : _bit_blackArmy.set(bit_F_Knight1);

							break;

							case static_cast<char>(Type::ROOK) :
								newFigure = new F_Rook(color, location);
								_blackArmy.pushBack(newFigure);

								(_bit_blackArmy.test(bit_F_Rook1)) ?
									_bit_blackArmy.set(bit_F_Rook2) : _bit_blackArmy.set(bit_F_Rook1);

								break;

								case static_cast<char>(Type::PAWN) :
									newFigure = new F_Pawn(color, location);
									_blackArmy.pushBack(newFigure);
									_pawnQuantity += 1;

									break;

								default:
									/*_logMessage = EnteringCustomString + ErrorTypeCustomString +
										col_type_loc.substr(0, 2) + L'\n';*/

									break;
		}

		//setting first move state
		if (col_type_loc[4] != L'1') {
			newFigure->_firstMove = false;
		}

		_board[location.x][location.y] = newFigure;

		/*_logMessage = EnteringCustomString + FigureIsPlacedString +
			col_type_loc.substr(0, 4) + L'\n';*/

		return;
	}
	else {
		/*_logMessage = EnteringCustomString + ErrorColorCustomString +
			col_type_loc.substr(0, 2) + L'\n';*/

		return;
	}
}

const cocos2d::Vector<Figure*>* Core::getWhiteArmy() const {
	return &_whiteArmy;
}

const cocos2d::Vector<Figure*>* Core::getBlackArmy() const {
	return &_blackArmy;
}

const cocos2d::Vector<Figure*>* Core::getCurrentArmy() const
{
	return _currentArmy;
}

const std::string& Core::getLogMessage() const {
	return _logMessage;
}

const bool Core::getGameOver() const
{
	return _gameOver;
}

const int Core::getHalfTurn() const
{
	return _halfTurn;
}

const std::pair<double, double> Core::getGameDuration()
{
	const auto tempTime = time(NULL);
	
	if (_halfTurn % 2) {
		_p1GameDuration += difftime(tempTime, _turnDuration);
	}
	else {
		_p2GameDuration += difftime(tempTime, _turnDuration);
	}

	_turnDuration = tempTime;

	return std::pair<double, double>(_p1GameDuration, _p2GameDuration);
}

const std::string& Core::getLastMove() const
{
	return _movesVector.back();
}
