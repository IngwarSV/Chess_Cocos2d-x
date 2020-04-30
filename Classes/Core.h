#pragma once

#include "cocos2d.h"

#include <iostream>
#include <string>
#include <bitset>

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

	//// for "en passant" actions 
	Figure* _enPassantFigure; // pawn that just made two-squares move
	Location _firstEnPassantPoint; // square that was skipped

	int _halfTurn; // game turns: halfTurn * 2
	bool _CHECK;
	bool _gameOver;
	//bool _moveCompleted;

	//std::wstring _command; // for command line instructions
	std::string _logMessage; // for game notifications

	Figure* _figureToMove = nullptr;

	// methods
	bool init();
	void initialSetup();

public:
	
	// methods
	static Core* sharedCore();

	

	void processEvent(Location newLocation);

	bool castling(Figure* king, Location currentLocation, Location newLocation);

	bool enPassant(Figure* figureToMove, Location currentLocation, Location newLocation);




	bool isKingInDanger(Figure* figureToMove, Location currentLocation, Location newLocation);

	void promotion(Figure* figureToMove, Location newPosition);

	void deletingFigure(Figure* enemyFigure);

	cocos2d::Vec2 convertCoord(Location location);

	void endTurn(Figure* figureToMove, Location currentLocation, Location newLocation);

	bool isCheck();

	bool isCheckmate();

	bool isDraw();







	//// getters
	//Figure* getFigureOnBoard(Location point) const;

	//std::vector<Location>* getPossibleMoves(Figure* figure);

	const cocos2d::Vector<Figure*>* getWhiteArmy() const;

	const cocos2d::Vector<Figure*>* getBlackArmy() const;

	const cocos2d::Vector<Figure*>* getCurrentArmy() const;
};