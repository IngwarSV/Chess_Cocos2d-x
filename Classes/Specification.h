#pragma once

#include <string>
#include "cocos2d.h"

struct Location {
	int x = 0, y = 0;

	bool operator==(const Location& other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const Location& other) const {
		return this->x != other.x || this->y != other.y;
	}
};

enum class Color : char {
	BLACK = 66,
	WHITE = 87
};

enum class Type : char {
	KING = 75,
	QUEEN = 81,
	BISHOP = 66,
	KNIGHT = 78,
	ROOK = 82,
	PAWN = 80
};

namespace DEF_SETT {
	// Board size
	constexpr int BOARD_SIZE = 8;

	// Board  bottom-left corner
	constexpr int BOARD_X = 73;
	constexpr int BOARD_Y = 104;

	// Board  bottom-left corner
	constexpr int SQUARE_SIZE = 73;

	//pawns quantity (for draw calculating)
	constexpr int PAWN_QUANTITY = 16;

	// Main font
	const std::string FONT{ "fonts/BOOK_ANTIQUA.ttf" };

	// UI COMPONENTS' POSITIONS
	const cocos2d::Vec2 LOG_MESS_POS{ 105.0f, 21.0f };
	const cocos2d::Vec2 SAVE_GAME_BUT{ 236.0f, 320.0f }; 
	const cocos2d::Vec2 LOAD_GAME_BUT{ 314.0f, 320.0f };
	const cocos2d::Vec2 GAME_SETT_BUT{ 392.0f, 320.0f };
	const cocos2d::Vec2 QUIT_BUT{ 470.0f, 320.0f };
	const cocos2d::Vec2 TIMER1_POS{ 754.0f, 443.0f };
	const cocos2d::Vec2 TIMER2_POS{ 914.0f, 443.0f };
	const cocos2d::Vec2 ACT_SIDE_POS1{ 790.0f, 575.0f };
	const cocos2d::Vec2 ACT_SIDE_POS2{ 945.0f, 575.0f };

	// Labels color
	const cocos2d::Color3B METALLIC_GOLD{ 212, 175, 55 };
	const cocos2d::Color3B CHOKOLATE{ 210,105,30 };


	// Images for sprites
	const std::string WK_ACT_ICON{ "WK_ACT_ForTurns.png" };
	const std::string WK_PAS_ICON{ "WK_PAS_ForTurns.png" };
	const std::string BK_ACT_ICON{ "BK_ACT_ForTurns.png" };
	const std::string BK_PAS_ICON{ "BK_PAS_ForTurns.png" };
	const std::string GOLDEN_Q_ICON{ "GoldenQueen.png" };
	const std::string GOLDEN_R_ICON{ "GoldenRook.png" };
	const std::string GOLDEN_H_ICON{ "GoldenHorse.png" };
	const std::string GOLDEN_B_ICON{ "GoldenBishop.png" };

	// Saved games path
	const std::string SAVED_GAMES_DIR = "\\SavedGames";

	// SCROLL_VIEW (for moves's log) STAFF
	//// SCROLL_VIEW_POS
	const cocos2d::Vec2 SCROLL_VIEW_POS{ 725.0f, 22.0f };
	//// SCROLL_VIEW_SIZE
	const cocos2d::Size SCROLL_VIEW_SIZE{ 290, 380 };
	//// Move label CoordX
	const float labelCoordX = 25.0f;
	//// Move labels' strings
	const std::string GAME_STARTED_STRING{ "\t\t\t\t Game started!" };
	const std::string WHITE_PL_STRING{ "White player:\t" };
	const std::string BLACK_PL_STRING{ "Black player: \t" };
	//// Labels' font size and distance between
	constexpr float LABEL_FONT_SIZE = 18.0f;
	constexpr float LABEL_DISTANCE = LABEL_FONT_SIZE + 2;
	
	//quitGameLabel
	const std::string QUIT_GAME_LABEL{ "Quit Game?" };
	


	// Figures' starting positions

	//// White Army
	const Location WR_INIT_POS1{ 0,0 };
	const Location WN_INIT_POS1{ 0,1 };
	const Location WB_INIT_POS1{ 0,2 };
	const Location WQ_INIT_POS{ 0,3 };
	const Location WK_INIT_POS{ 0,4 };
	const Location WB_INIT_POS2{ 0,5 };
	const Location WN_INIT_POS2{ 0,6 };
	const Location WR_INIT_POS2{ 0,7 };
	const Location WP_INIT_POS1{ 1,0 };

	//// Black Army
	const Location BR_INIT_POS1{ 7,0 };
	const Location BN_INIT_POS1{ 7,1 };
	const Location BB_INIT_POS1{ 7,2 };
	const Location BQ_INIT_POS{ 7,3 };
	const Location BK_INIT_POS{ 7,4 };
	const Location BB_INIT_POS2{ 7,5 };
	const Location BN_INIT_POS2{ 7,6 };
	const Location BR_INIT_POS2{ 7,7 };
	const Location BP_INIT_POS1{ 6,0 };

	// serial number of bits for 8 figures: N1, N2, B1, B2, R1, R2, Q1, Q2 in bitsets
	const int bit_F_Knight1 = 0;
	const int bit_F_Knight2 = 1;
	const int bit_F_Bishop1 = 2;
	const int bit_F_Bishop2 = 3;
	const int bit_F_Rook1 = 4;
	const int bit_F_Rook2 = 5;
	const int bit_F_Queen1 = 6;
	const int bit_F_Queen2 = 7;

	// Log Messages
	const std::string NewGameString{ "New Game!" };
	const std::string CastlingPerfomed{ "Castling is done: " };
	const std::string CastlingShort{ "O-O  " };
	const std::string CastlingLong{ "O-O-O" };
	const std::string EnPassantPerformedString{ "En passant is made: " };
	const std::string ErrorMoveIsIllegal{ "Figure can't move: " };
	const std::string ErrorKingIsInDanger{ "Your King is in danger if: " };
	const std::string PreviousMoveString{ "Previous move: " };
	const std::string WarningCheckString{ " Warning: CHECK!" };
	const std::string WarningCheckmateString{ " CHECKMATE: GAME OVER!" };
	const std::string ChoosePromotionString{ "Choose promotion: Q, B, N, R" };
	const std::string PromotionSuccessString = "Promotion successful!";

}


const std::wstring ErrorInvalidMoveParam = L"Invalid move command, enter e.g.: (A2 A4): ";
const std::wstring ErrorInvalidPos1 = L"Invalid parameter for current position of figure: ";
const std::wstring ErrorInvalidPos2 = L"Invalid parameter for new position of figure: ";
const std::wstring ErrorInvalidPos3 = L"No figure in your set on the position: ";
const std::wstring enPassantPerformedString = L"enPassant executed: ";


const std::wstring ErrorPromotionType2 = L"\nChoose promotion (Q), (B), (N), (R)\n";
const std::wstring DrawStalemateString = L"DRAW: stalemate\n";
const std::wstring impossibleCheckmate1 = L"DRAW: two kings left\n";
const std::wstring impossibleCheckmate2 =
L"DRAW: king with/without bishop versus king and\nbishop(bishops) on the same color\n";
const std::wstring impossibleCheckmate3 = L"DRAW: king and knight versus king\n";
const std::wstring EnteringCustomString =
L"Custom mode: (D)one, (Q)uit,\nPlace figures: (WQA2), (BBC7),\n(BKE81)-\"1\"-true for first move\n";
const std::wstring ErrorPlaceKingsString = L"Please place black and white kings\n";
const std::wstring ChooseSideToMoveString = L"Choose side to move first: W / B ?\n";
const std::wstring NewCustomGameString = L"New Custom Game!\n";
const std::wstring ErrorDataCustomString = L"Invalid data to place figure\n";
const std::wstring ErrorLocCustomString = L"Invalid parameter for location of figure: ";
const std::wstring ErrorLocOccupiedCustomString = L"Location is occupied: ";
const std::wstring ErrorTypeCustomString = L"Invalid parameter for type of the figure: ";
const std::wstring ErrorColorCustomString = L"Invalid parameter for color of the figure: ";
const std::wstring FigureIsPlacedString = L"Figure is placed: ";
const std::wstring SaveGameAsString = L"Save as: ";
const std::wstring SuccessSaveGameString = L"File saved as: ";
const std::wstring ErrorSaveGameString = L"Error create file: ";
const std::wstring ErrorLoadGameString = L"No files to load\n";
const std::wstring ChooseLoadFileString = L"Choose file (print name without .txt):\n";
const std::wstring NoSuchLoadFileString = L"No such file in directory: ";
const std::wstring LoadGameSuccessString = L"Successfully loaded: ";



