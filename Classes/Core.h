#pragma once

#include "cocos2d.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <bitset>
//#include <algorithm>

#include "Specification.h"
#include "Figure.h"
#include "Units.h"

using namespace DEF_SETT;


class Core {
private:
// attributes

	//// Board[SIZE][SIZE], BOARD_SIZE = 8;
	Figure*** _board;

	//// sets for "White" and "Black" armies and pointers on them
	cocos2d::Vector<Figure*> _whiteArmy = cocos2d::Vector<Figure*>(16);
	cocos2d::Vector<Figure*> _blackArmy = cocos2d::Vector<Figure*>(16);
	cocos2d::Vector<Figure*>* _currentArmy;
	cocos2d::Vector<Figure*>* _enemyArmy;
	

	//// bitsets 0111 1111 for 8 figures (B1, B2, N1, N2, R1, R2, Q1, Q2) in army 
	std::bitset<BOARD_SIZE> _bit_whiteArmy{ 127 };// including 1 place for promoted Queen 
	std::bitset<BOARD_SIZE> _bit_blackArmy{ 127 };

	int _pawnQuantity; //pawns quantity (for draw calculatings)

	////// pointers on kings for quick access
	Figure* _WKing;
	Figure* _BKing;
	Figure* _activeKing;

	//// temp data for "en passant" actions 
	Figure* _enPassantFigure; // pawn that just made two-squares move
	//Location _firstEnPassantPoint; // square that was skipped
	//// temp data for "promotion" actions 
	Figure* _figureToPromote; // pawn that reached board edge
	//Location _promotedFigPreviousLocation; // figureToPromote previous location
	Location _tempLocation; // figureToPromote previous location

	int _halfTurn; // game turns: halfTurn * 2
	bool _CHECK;
	bool _gameOver;
	double _p1GameDuration;
	double _p2GameDuration;

	

	//std::chrono::system_clock::time_point _turnDuration;

	time_t _turnDuration;
	
	// storing moves
	std::vector<std::string> _movesVector;
	//std::wstring _command; // for command line instructions
	std::string _logMessage; // for game notifications

	Figure* _figureToMove;

// methods
	bool init();

	cocos2d::Vec2 convertCoord(Location location);
	std::string getMoveString(Location currentLocation, Location newLocation);
	void parseFigureDataString(std::string col_type_loc); //parsing string into figure's data

	


public:
// attributes
	// storing testsResults
	std::vector<std::string> _testsResults;
	
// methods
	static Core* sharedCore();

	void initialSetup();

	void saveData(std::string filename);

	void loadData(const std::string& gameDataString, 
		const std::string& wArmyDataString, const std::string& bArmyDataString, std::string filename);

	void clearData(); // deleting existing game data to load saved game / customize new game

	bool processEvent(Location newLocation);

	bool castling(Figure* king, Location currentLocation, Location newLocation);

	bool enPassant(Figure* figureToMove, Location currentLocation, Location newLocation);

	bool isKingInDanger(Figure* figureToMove, Location currentLocation, Location newLocation);

	void arrangePromotion(Figure* figureToMove);

	void executePromotion(Figure* figureToMove, Type figureType);

	void deletingFigure(Figure* enemyFigure);

	void makeMove(Figure* figureToMove, Location currentLocation, Location newLocation);

	bool endTurn(Location currentLocation, Location newLocation);

	bool isCheck();

	bool isCheckmate();

	bool isDraw();

	

	void startTurnDurationCount();

	
	//// getters
	const cocos2d::Vector<Figure*>* getWhiteArmy() const;

	const cocos2d::Vector<Figure*>* getBlackArmy() const;

	const cocos2d::Vector<Figure*>* getCurrentArmy() const;

	Figure* getActiveKing() const;

	const std::string& getLogMessage() const;

	const bool getGameOver() const;

	const int getHalfTurn() const;

	const std::pair<double, double> getGameDuration();

	const std::vector<std::string>* getMovesVector() const;

	const std::string& getLastMove() const;

	Figure* getFigureOnBoard(Location point) const;

	//setters
	void setLogMessage(std::string logMessage);
	
};