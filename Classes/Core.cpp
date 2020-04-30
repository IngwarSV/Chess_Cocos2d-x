#include "Core.h"

using namespace cocos2d;

static bool s_firstRun = true;
static Core s_sharedCore;

void Core::initialSetup()
{
	//Setting board with nullptrs
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			_board[i][j] = nullptr;
		}
	}

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

	// for "en passant" actions 
	_enPassantFigure = nullptr; // pawn that just made two-squares move
	_firstEnPassantPoint = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
	_halfTurn = 1;
	_CHECK = false;
	_gameOver = false;
	//_moveCompleted = false;

	//_command = L"\n";
	//_logMessage = NewGameString;
}


bool Core::init() {
	// creating Board[8][8]
	this->_board = new Figure * *[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; ++i) {
		_board[i] = new Figure * [BOARD_SIZE];
	}

	auto spritecache = SpriteFrameCache::getInstance();

	spritecache->addSpriteFramesWithFile("GameImages.plist");

	initialSetup();

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






void Core::processEvent(Location newLocation)
{
	Figure* newFigureToMove = _board[newLocation.x][newLocation.y];

	if (_currentArmy->contains(newFigureToMove)) {
		if (_figureToMove) {
			_figureToMove->setPassiveState();
		}
		//setting previous figureToMove in inActive state
		_figureToMove = newFigureToMove;
		_figureToMove->setActiveState();

		return;
	}

	if (!_figureToMove) {
		return;
	}

	Location currentLocation = _figureToMove->getLocation();

	//castling checking, execution if true
	if (castling(_figureToMove, currentLocation, newLocation)) {
		// rook movement
		Location rookPosition;
		Location rookNewPosition;
		if (newLocation.y > currentLocation.y) {
			rookPosition = Location{ currentLocation.x, BOARD_SIZE - 1 };
			rookNewPosition = Location{ currentLocation.x, newLocation.y - 1 };
		}
		else {
			rookPosition = Location{ currentLocation.x, 0 };
			rookNewPosition = Location{ currentLocation.x, newLocation.y + 1 };
		}
		Figure* rook = _board[rookPosition.x][rookPosition.y];

		_board[rookPosition.x][rookPosition.y] = nullptr;
		_board[rookNewPosition.x][rookNewPosition.y] = rook;
		rook->setLocation(rookNewPosition);
		rook->_firstMove = false;
		rook->runAction(MoveTo::create(0.1f, convertCoord(rookNewPosition)));

		// deleting data for En passant
		_enPassantFigure = nullptr;
		_firstEnPassantPoint = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

		//_logMessage = CastlingPerfomed + _command.substr(0, 5) + L'\n';
		
		endTurn(_figureToMove, currentLocation, newLocation);

		return;
	}


	// en passant checking, execution if true
	if (enPassant(_figureToMove, currentLocation, newLocation)) {
		Location secondEnPassantPoint = _enPassantFigure->getLocation();

		deletingFigure(_enPassantFigure);
		/*_board[currentLocation.x][currentLocation.y] = nullptr;
		_board[secondEnPassantPoint.x][secondEnPassantPoint.y] = nullptr;
		_board[newLocation.x][newLocation.y] = _figureToMove;
		_figureToMove->setLocation(newLocation);*/

		// deleting data for En passant
		_enPassantFigure = nullptr;
		_firstEnPassantPoint = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

		//_logMessage = enPassantPerformedString + _command.substr(0, 5) + L'\n';
		
		endTurn(_figureToMove, currentLocation, newLocation);

		return;
	}


	// checking if figureToMove can execute command
	bool moveIsLegal = false;
	auto v_possibleMoves = _figureToMove->getPossibleMoves(_board);

	for (auto possiblePosition : *v_possibleMoves) {
		if (newLocation == possiblePosition) {
			moveIsLegal = true;
			/*_figureToMove->runAction(MoveTo::create(0.1f, Vec2(static_cast<float>(BOARD_X + newLocation.y * SQUARE_SIZE),
				static_cast<float>(BOARD_Y + newLocation.x * SQUARE_SIZE))));
			_figureToMove->setLocation(newLocation);
			_figureToMove->setGlobalZOrder(BOARD_SIZE - newLocation.x);*/
			break;
		}
	}

	if (!moveIsLegal) {
		//TODO_logMessage = ErrorMoveIsIllegal + _command.substr(0, 5) + L'\n';

		return;
	}
		

	// checking if figure's movement doesn't endanger the king
	if (isKingInDanger(_figureToMove, currentLocation, newLocation)) {
		//_logMessage = ErrorKingIsInDanger + _command.substr(0, 5) + L'\n';
		//_moveCompleted = false;
		return;
	}

	// deleting data for En passant
	_enPassantFigure = nullptr;
	_firstEnPassantPoint = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

	//checking for new En passant data
	if (_figureToMove->_firstMove) {
		if (_figureToMove->getType() == Type::PAWN) {
			int delta = newLocation.x - currentLocation.x;

			if (delta == 2) {
				_enPassantFigure = _figureToMove;
				_firstEnPassantPoint = Location{ newLocation.x - 1, newLocation.y };
			}
			else if (delta == -2) {
				_enPassantFigure = _figureToMove;
				_firstEnPassantPoint = Location{ newLocation.x + 1, newLocation.y };
			}
		}
	}

	// Removing enemy's figure (if needed) and moving figure on new position
	Figure* enemyFigure = _board[newLocation.x][newLocation.y];

	if (enemyFigure) {
		deletingFigure(enemyFigure);
	}

	
	//_logMessage = PreviousMoveString + _command.substr(0, 5) + L'\n';

	// checking for promotion
	if (_figureToMove->getType() == Type::PAWN && (newLocation.x == 0 || newLocation.x == BOARD_SIZE - 1)) {
		promotion(_figureToMove, newLocation);
	}

	endTurn(_figureToMove, currentLocation, newLocation);

	return;
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
		if (newLocation == _firstEnPassantPoint) {
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

void Core::promotion(Figure* figureToMove, Location newPosition)
{
	////std::wstring previousMoveString = _logMessage;
	//Color color = figureToMove->getFigureColor();
	//std::string figureType;
	//Figure* promotedFigure = nullptr;
	//std::bitset<BOARD_SIZE>* bit_currentArmy;
	//bit_currentArmy = (_halfTurn % 2) ? &_bit_whiteArmy : &_bit_blackArmy;

	////_logMessage = ChoosePromotionString;

	//while (true) {
	//	drawGameField();
	//	std::wcout << ENTER_COMMAND_STRING;

	//	std::getline(std::wcin, figureType);

	//	if (figureType[0] == static_cast<wchar_t>(Type::QUEEN)) {
	//		promotedFigure = new F_Queen(color, newPosition);

	//		(bit_currentArmy->test(bit_F_Queen1)) ?
	//			bit_currentArmy->set(bit_F_Queen2) : bit_currentArmy->set(bit_F_Queen1);

	//		break;
	//	}
	//	else if (figureType[0] == static_cast<wchar_t>(Type::BISHOP)) {
	//		promotedFigure = new F_Bishop(color, newPosition);

	//		((newPosition.x + newPosition.y) % 2) ?
	//			bit_currentArmy->set(bit_F_Bishop1) : bit_currentArmy->set(bit_F_Bishop2);

	//		break;
	//	}
	//	else if (figureType[0] == static_cast<wchar_t>(Type::KNIGHT)) {
	//		promotedFigure = new F_Knight(color, newPosition);

	//		(bit_currentArmy->test(bit_F_Knight1)) ?
	//			bit_currentArmy->set(bit_F_Knight2) : bit_currentArmy->set(bit_F_Knight1);

	//		break;
	//	}
	//	else if (figureType[0] == static_cast<wchar_t>(Type::ROOK)) {
	//		promotedFigure = new F_Rook(color, newPosition);

	//		(bit_currentArmy->test(bit_F_Rook1)) ?
	//			bit_currentArmy->set(bit_F_Rook2) : bit_currentArmy->set(bit_F_Rook1);

	//		break;
	//	}

	//	_logMessage = ErrorPromotionType1 + figureType[0] + ErrorPromotionType2;
	//}

	//// deleting pawn
	//_currentArmy->erase(figureToMove);
	//delete figureToMove;
	//_pawnQuantity -= 1;

	//// setting new figure
	//_board[newPosition.x][newPosition.y] = promotedFigure;
	//_currentArmy->insert(promotedFigure);

	//_logMessage = previousMoveString;
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
			//_logMessage += ErrorCheckString;

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
				//_logMessage += ErrorCheckString;

				return false;
			}
		}

		//// checking if enPassant can be performed to protect the king
		if (figure->getType() == Type::PAWN && _enPassantFigure) {
			if (enPassant(figure, figure->getLocation(), _firstEnPassantPoint)) {
				//_logMessage += ErrorCheckString;

				return false;
			}
		}
	}

	// Game Over
	//_logMessage += ErrorCheckmateString;

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
			if (enPassant(figure, figure->getLocation(), _firstEnPassantPoint)) {
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

	bit_enemyArmy = (_halfTurn % 2) ?
		&_bit_blackArmy : bit_enemyArmy = &_bit_whiteArmy;

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

	_enemyArmy->eraseObject(enemyFigure);
	delete enemyFigure;
}

Vec2 Core::convertCoord(Location location)
{
	return Vec2(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
}

void Core::endTurn(Figure* figureToMove, Location currentLocation, Location newLocation)
{
	_board[currentLocation.x][currentLocation.y] = nullptr;
	_board[newLocation.x][newLocation.y] = _figureToMove;
	figureToMove->setLocation(newLocation);
	figureToMove->_firstMove = false;
	figureToMove->runAction(MoveTo::create(0.1f, convertCoord(newLocation)));
	figureToMove->setGlobalZOrder(BOARD_SIZE - newLocation.x);
	figureToMove->setPassiveState();
	figureToMove = nullptr;
	_halfTurn += 1;
	_CHECK = false;

	

	// updating pointers for quick access
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

	if (isCheck()) {
		_CHECK = true;
		if (isCheckmate()) {
			_gameOver = true;
		}
	}
	else if (isDraw()) {
		_gameOver = true;
	}
}


// getters
//Figure* Core::getFigureOnBoard(Location location) const {
//	return _board[location.x][location.y];
//}

//std::vector<Location>* Core::getPossibleMoves(Figure* figure)
//{
//	return figure->getPossibleMoves(_board);
//}

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
