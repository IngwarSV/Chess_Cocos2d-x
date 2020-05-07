#include "pch.h"

#include "../Classes/AppDelegate.h"
#include "../Classes/GameMenu.h"
#include "../Classes/NewGameLayer.h"
#include "../Classes/Core.h"
#include "../Classes/Figure.h"
#include "../Classes/Units.h"
//#include "cocos2d.h"
//#include "../cocos2d/cocos/cocos2d.h"


class GameTest : public ::testing::Test {
protected:
    GameTest() {
        // You can do set-up work for each test here.
    }

    ~GameTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
    AppDelegate app;
    Core* _core = Core::sharedCore();
};


TEST_F(GameTest, TestInitialSetup) {
    ////figures in initial position
    //EXPECT_EQ(game.getBoard(BR_INIT_POS1)->getFigureName(), L"BR") << L"black rook1 in initial position";
    //EXPECT_EQ(game.getBoard(BN_INIT_POS1)->getFigureName(), L"BN") << L"black knight1 in initial position";
    //EXPECT_EQ(game.getBoard(BB_INIT_POS1)->getFigureName(), L"BB") << L"black bishop1 in initial position";
    //EXPECT_EQ(game.getBoard(BQ_INIT_POS)->getFigureName(), L"BQ") << L"black queen in initial position";
    //EXPECT_EQ(game.getBoard(BK_INIT_POS)->getFigureName(), L"BK") << L"black king in initial position";
    //EXPECT_EQ(game.getBoard(BB_INIT_POS2)->getFigureName(), L"BB") << L"black bishop2 in initial position";
    //EXPECT_EQ(game.getBoard(BN_INIT_POS2)->getFigureName(), L"BN") << L"black knight2 in initial position";
    //EXPECT_EQ(game.getBoard(BR_INIT_POS2)->getFigureName(), L"BR") << L"black rook2 in initial position";

    //EXPECT_EQ(game.getBoard(WR_INIT_POS1)->getFigureName(), L"WR") << L"white rook1 in initial position";
    //EXPECT_EQ(game.getBoard(WN_INIT_POS1)->getFigureName(), L"WN") << L"white knight1 in initial position";
    //EXPECT_EQ(game.getBoard(WB_INIT_POS1)->getFigureName(), L"WB") << L"white bishop1 in initial position";
    //EXPECT_EQ(game.getBoard(WQ_INIT_POS)->getFigureName(), L"WQ") << L"white queen in initial position";
    //EXPECT_EQ(game.getBoard(WK_INIT_POS)->getFigureName(), L"WK") << L"white king in initial position";
    //EXPECT_EQ(game.getBoard(WB_INIT_POS2)->getFigureName(), L"WB") << L"white bishop2 in initial position";
    //EXPECT_EQ(game.getBoard(WN_INIT_POS2)->getFigureName(), L"WN") << L"white knight2 in initial position";
    //EXPECT_EQ(game.getBoard(WR_INIT_POS2)->getFigureName(), L"WR") << L"white rook2 in initial position";

    ////pawns in initial position
    //for (int y = 0; y < BOARD_SIZE - 1; ++y) {
    //    EXPECT_EQ(game.getBoard(Point{ 1, y })->getFigureName(), L"BP") << L"black pawns in initial position";
    //    EXPECT_EQ(game.getBoard(Point{ 6, y })->getFigureName(), L"WP") << L"white pawns in initial position";
    //}

    //// nullptrs from x = 2 to 5
    //for (int x = 2; x < BOARD_SIZE - 2; ++x) {
    //    for (int y = 0; y < BOARD_SIZE - 1; ++y) {
    //        EXPECT_EQ(game.getBoard(Point{ x, y }), nullptr) << L"nullptrs from x = 2 to 5";
    //    }
    //}

    //EXPECT_EQ(game.getWhiteArmy()->size(), 16);
    //EXPECT_EQ(game.getBlackArmy()->size(), 16);

    //EXPECT_EQ(game.getCurrentArmy(), game.getWhiteArmy());
    //EXPECT_EQ(game.getEnemyArmy(), game.getBlackArmy());

    //EXPECT_EQ(game.getBArmyBit().to_ulong(), 127UL);
    //EXPECT_EQ(game.getWArmyBit().count(), BOARD_SIZE - 1);

    //EXPECT_EQ(game.getEnPassantFigure(), nullptr);
    //Point point{ BOARD_SIZE, BOARD_SIZE };
    //EXPECT_EQ(game.getFirstEnPassantPoint(), point);

    //EXPECT_EQ(game.getHalfTurn(), 0);
    //EXPECT_EQ(game.getCHECKStatus(), false);
    //EXPECT_EQ(game.getGameOverStatus(), false);
    //EXPECT_EQ(game.getMoveCompletedStatus(), false);

    //EXPECT_EQ(game.getCurrentCommand(), L"\n");
    //EXPECT_EQ(game.getLogMessage(), NewGameString);
}

TEST_F(GameTest, TestIsCheck) {
    // WK is in check under attack by BQ
    _core->loadGameDataString("1 8 8 8 8 WKA80 BQA50 BKC40");
    EXPECT_EQ(_core->isCheck(), true);

    // WK is not in check
    _core->loadGameDataString("1 8 8 8 8 WKB80 BQA50 BKC40");
    EXPECT_EQ(_core->isCheck(), false);
}

TEST_F(GameTest, isCheckmate) {
    // Black king is checkmated with a rook
    _core->loadGameDataString("0 8 8 8 8 WKF5 WRH1 BKH5");
    EXPECT_EQ(_core->isCheckmate(), true);

    // Black king is not checkmated with a rook, black knight can cover black king
    _core->loadGameDataString("0 8 8 8 8 WKF5 WRH1 BNG2 BKH5");
    EXPECT_EQ(_core->isCheckmate(), false);

    // Black king is checkmated with a bishop and a knight
    _core->loadGameDataString("0 8 8 8 8 WKG6 WBF6 WNH6 BKH8");
    EXPECT_EQ(_core->isCheckmate(), true);

    // Black king is not checkmated with a bishop and a knight, black rook can attack white bishop
    _core->loadGameDataString("0 8 8 8 8 WKG6 WBF6 WNH6 BRA6 BKH8");
    EXPECT_EQ(_core->isCheckmate(), false);

    // checking if enPassant can be performed to protect the king
    //// Black pawn, which has just advanced for two squares, checkmates the white king
    _core->loadGameDataString("1 3 1 2 1 WKA4 BNC6 BRH3 BKE8 BPB5 BQB8");
    EXPECT_EQ(_core->isCheckmate(), true);

    //// Black pawn, which has just advanced for two squares, can be captured en passant by white pawn
    _core->loadGameDataString("1 3 1 2 1 WKA4 WPC5 BNC6 BRH3 BKE8 BPB5 BQB8");
    EXPECT_EQ(_core->isCheckmate(), false);
}

TEST_F(GameTest, isDraw) {
    // checking stalemate
    ////Black are in stalemate
    _core->loadGameDataString("0 8 8 8 8 WKF7 WQG6 WPB2 WPC3 BPB3 BKH8");
    EXPECT_EQ(_core->isDraw(), true);

    ////Black are not in stalemate, because of en passant move
    _core->loadGameDataString("0 5 2 6 2 WKF7 WQG6 WPB2 WPC3 BPB3 BKH8");
    EXPECT_EQ(_core->isDraw(), false);


    // checking impossibility of checkmate
    //// two kings left
    _core->loadGameDataString("0 8 8 8 8 WKF7 BKH8");
    EXPECT_EQ(_core->isDraw(), true);

    //// two kings and one white pawn left
    _core->loadGameDataString("0 8 8 8 8 WKF7 WPB5 BKH8");
    EXPECT_EQ(_core->isDraw(), false);

    //// two kings and one black pawn left
    _core->loadGameDataString("0 8 8 8 8 WKF7 BPB5 BKH8");
    EXPECT_EQ(_core->isDraw(), false);

    //// king with/without bishop versus king and bishop(bishops) on the same color
    //// king versus king and bishop
    _core->loadGameDataString("0 8 8 8 8 WKF7 WBB5 BKH8");
    EXPECT_EQ(_core->isDraw(), true);

    //// king versus king and bishops on the same color
    _core->loadGameDataString("0 8 8 8 8 WKF7 WBB5 WBC6 BKH8");
    EXPECT_EQ(_core->isDraw(), true);

    //// king with bishop versus king and bishops on the same color
    _core->loadGameDataString("0 8 8 8 8 WKF7 WBB5 WBC6 BKH8 BBD5");
    EXPECT_EQ(_core->isDraw(), true);

    //// king with bishop versus king and bishops on the different colors
    _core->loadGameDataString("0 8 8 8 8 WKF7 WBB5 WBC6 BKH8 BBD4");
    EXPECT_EQ(_core->isDraw(), false);

    //// king and knight versus king
    _core->loadGameDataString("0 8 8 8 8 WKF7 BKH8 BND5");
    EXPECT_EQ(_core->isDraw(), true);
}


//TEST_F(GameTest, castling) {
//    // cheking for castling, no restrictions
//
//    //// white king with kingside rook
//    game.loadGameDataString(L"1 8 8 8 8 WKE11 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,6 }), true);
//
//    //// black king with kingside rook
//    game.loadGameDataString(L"0 8 8 8 8 WKE11 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 0,4 }, Point{ 0,6 }), true);
//
//    //// white king with queenside rook
//    game.loadGameDataString(L"1 8 8 8 8 WKE11 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), true);
//
//    //// black king with queenside rook
//    game.loadGameDataString(L"0 8 8 8 8 WKE11 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 0,4 }, Point{ 0,2 }), true);
//
//
//    // cheking for castling, king is under attack
//
//    //// white king is under attack
//    game.loadGameDataString(L"1 8 8 8 8 WKE11 WRH11 WRA11 BKE81 BRE70 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//    //// black king is under attack
//    game.loadGameDataString(L"0 8 8 8 8 WKE11 WRE20 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//
//    // cheking for castling, rook has moved before
//
//    //// white king with kingside rook
//    game.loadGameDataString(L"1 8 8 8 8 WKE11 WRH10 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,6 }), false);
//
//    //// black king with kingside rook
//    game.loadGameDataString(L"0 8 8 8 8 WKE11 WRH11 WRA11 BKE81 BRH80 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 0,4 }, Point{ 0,6 }), false);
//
//    //// white king with queenside rook
//    game.loadGameDataString(L"1 8 8 8 8 WKE11 WRH11 WRA10 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//    //// black king with queenside rook
//    game.loadGameDataString(L"0 8 8 8 8 WKE11 WRH11 WRA11 BKE81 BRH81 BRA80");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 0,4 }, Point{ 0,2 }), false);
//
//
//    // cheking for castling, king has moved before
//
//    //// white king with kingside rook
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,6 }), false);
//
//    //// black king with kingside rook
//    game.loadGameDataString(L"0 8 8 8 8 WKE11 WRH11 WRA11 BKE80 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 0,4 }, Point{ 0,6 }), false);
//
//
//    // cheking for castling, squares between king and rook are not empty
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WBB1 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WBC1 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WBD1 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WBF1 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,6 }), false);
//
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WBG1 WRH11 WRA11 BKE81 BRH81 BRA81");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,6 }), false);
//
//    // cheking for castling, squares between king and rook are under attack
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WRH11 WRA11 BKE81 BRH81 BRA81 BQB8");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WRH11 WRA11 BKE81 BRH81 BRA81 BQC8");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WRH11 WRA11 BKE81 BRH81 BRA81 BQD8");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,2 }), false);
//
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WRH11 WRA11 BKE81 BRH81 BRA81 BQF8");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,6 }), false);
//
//    game.loadGameDataString(L"1 8 8 8 8 WKE10 WRH11 WRA11 BKE81 BRH81 BRA81 BQG8");
//    EXPECT_EQ(game.castling(game.getActiveKing(), Point{ 7,4 }, Point{ 7,6 }), false);
//}
//
//TEST_F(GameTest, enPassant) {
//    // cheking for enPassant, no restriction
//    game.loadGameDataString(L"1 3 1 2 1 WKC10 WPC50 BKB80 BPB50");
//    Figure* figureToMove = game.getBoard(Point{ 3, 2 });
//
//    EXPECT_EQ(game.enPassant(figureToMove, Point{ 3,2 }, Point{ 2,1 }), true);
//
//    game.loadGameDataString(L"0 5 2 6 2 WKC10 WPC30 BKB80 BPB30");
//    figureToMove = game.getBoard(Point{ 5, 1 });
//
//    EXPECT_EQ(game.enPassant(figureToMove, Point{ 5,1 }, Point{ 6,2 }), true);
//
//    // cheking for enPassant, king is under attack in case enPassant
//    game.loadGameDataString(L"1 3 1 2 1 WKC10 WPC50 BKB80 BPB50 BRC80");
//    figureToMove = game.getBoard(Point{ 3, 2 });
//
//    EXPECT_EQ(game.enPassant(figureToMove, Point{ 3,2 }, Point{ 2,1 }), false);
//
//    game.loadGameDataString(L"0 5 2 6 2 WKC10 WPC30 WRB10 BKB80 BPB30");
//    figureToMove = game.getBoard(Point{ 5, 1 });
//
//    EXPECT_EQ(game.enPassant(figureToMove, Point{ 5,1 }, Point{ 6,2 }), false);
//}
//
//TEST_F(GameTest, isKingInDanger) {
//    // King is not attacked due to the movement of the figure
//
//    //// white pawn moves
//    game.loadGameDataString(L"1 8 8 8 8 WKE11 WPD21 BKE81 BBF81");
//    Figure* figureToMove = game.getBoard(Point{ 6, 3 });
//
//    EXPECT_EQ(game.isKingInDanger(figureToMove, Point{ 6,3 }, Point{ 4,3 }), false);
//
//    //// black bishop moves
//    game.loadGameDataString(L"0 8 8 8 8 WKE11 WPD21 BKE81 BBF81");
//    figureToMove = game.getBoard(Point{ 0, 5 });
//
//    EXPECT_EQ(game.isKingInDanger(figureToMove, Point{ 0,5 }, Point{ 1,4 }), false);
//
//
//    // King is attacked due to the movement of the figure
//
//    //// white pawn moves, king is under attack of black bishop
//    game.loadGameDataString(L"1 8 8 8 8 WKE11 WPD21 BKE81 BBF81 BBA50");
//    figureToMove = game.getBoard(Point{ 6, 3 });
//
//    EXPECT_EQ(game.isKingInDanger(figureToMove, Point{ 6,3 }, Point{ 4,3 }), true);
//
//    //// black bishop moves, king is under attack of white rook
//    game.loadGameDataString(L"0 8 8 8 8 WKE11 WPD21 WRH80 BKE81 BBF81");
//    figureToMove = game.getBoard(Point{ 0, 5 });
//
//    EXPECT_EQ(game.isKingInDanger(figureToMove, Point{ 0,5 }, Point{ 1,4 }), true);
//
//    // King is attacked due to his movement
//    //// White king is under attack in case of movement
//    game.loadGameDataString(L"1 8 8 8 8 WKF10 BKE81 BBF81 BBA50");
//    figureToMove = game.getBoard(Point{ 7, 5 });
//
//    EXPECT_EQ(game.isKingInDanger(figureToMove, Point{ 7,5 }, Point{ 7,4 }), true);
//
//    //// Black king is under attack in case of movement
//    game.loadGameDataString(L"0 8 8 8 8 WKF10 BKE71 WRH80");
//    figureToMove = game.getBoard(Point{ 1, 4 });
//
//    EXPECT_EQ(game.isKingInDanger(figureToMove, Point{ 1,4 }, Point{ 0,4 }), true);
//}
//
//TEST_F(GameTest, queenPromotion1) {
//    // Promotion of white pawn to queen (without exsisting one)
//    game.loadGameDataString(L"1 8 8 8 8 WKE21 WPD80 BKE81 BBF81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 0);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 0, 3 });
//    std::wcin.putback(L'Q');
//    game.promotion(figureToMove, Point{ 0, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 0, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"WQ");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 64);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from whiteArmy set
//    EXPECT_EQ(game.getWhiteArmy()->find(figureToMove), game.getWhiteArmy()->end());
//
//    ////queen is inserted in whiteArmy set
//    EXPECT_NE(game.getWhiteArmy()->find(promotedFigure), game.getWhiteArmy()->end());
//}
//
//TEST_F(GameTest, queenPromotion2) {
//    // Promotion of white pawn to queen (with exsisting one)
//    game.loadGameDataString(L"1 8 8 8 8 WKE21 WQD11 WPD80 BKE81 BBF81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 64);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 0, 3 });
//    std::wcin.putback(L'Q');
//    game.promotion(figureToMove, Point{ 0, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 0, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"WQ");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 192);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from whiteArmy set
//    EXPECT_EQ(game.getWhiteArmy()->find(figureToMove), game.getWhiteArmy()->end());
//
//    ////queen is inserted in whiteArmy set
//    EXPECT_NE(game.getWhiteArmy()->find(promotedFigure), game.getWhiteArmy()->end());
//}
//
//TEST_F(GameTest, queenPromotion3) {
//    // Promotion of white pawn to queen (with two exsisting)
//    game.loadGameDataString(L"1 8 8 8 8 WKE21 WQD11 WQD20 WPD80 BKE81 BBF81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 192);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 0, 3 });
//    std::wcin.putback(L'Q');
//    game.promotion(figureToMove, Point{ 0, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 0, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"WQ");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 192);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from whiteArmy set
//    EXPECT_EQ(game.getWhiteArmy()->find(figureToMove), game.getWhiteArmy()->end());
//
//    ////queen is inserted in whiteArmy set
//    EXPECT_NE(game.getWhiteArmy()->find(promotedFigure), game.getWhiteArmy()->end());
//}
//
//TEST_F(GameTest, knightPromotion1) {
//    // Promotion of white pawn to knight (without exsisting one)
//    game.loadGameDataString(L"1 8 8 8 8 WKE21 WPD80 BKE81 BBF81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 0);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 0, 3 });
//    std::wcin.putback(L'N');
//    game.promotion(figureToMove, Point{ 0, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 0, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"WN");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 1);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from whiteArmy set
//    EXPECT_EQ(game.getWhiteArmy()->find(figureToMove), game.getWhiteArmy()->end());
//
//    ////knight is inserted in whiteArmy set
//    EXPECT_NE(game.getWhiteArmy()->find(promotedFigure), game.getWhiteArmy()->end());
//}
//
//TEST_F(GameTest, knightPromotion2) {
//    // Promotion of white pawn to knight (with exsisting one)
//    game.loadGameDataString(L"1 8 8 8 8 WKE21 WND11 WPD80 BKE81 BBF81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 1);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 0, 3 });
//    std::wcin.putback(L'N');
//    game.promotion(figureToMove, Point{ 0, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 0, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"WN");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getWArmyBit().to_ulong(), 3);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from whiteArmy set
//    EXPECT_EQ(game.getWhiteArmy()->find(figureToMove), game.getWhiteArmy()->end());
//
//    ////knight is inserted in whiteArmy set
//    EXPECT_NE(game.getWhiteArmy()->find(promotedFigure), game.getWhiteArmy()->end());
//}
//
//TEST_F(GameTest, rookPromotion1) {
//    // Promotion of black pawn to rook (without exsisting one)
//    game.loadGameDataString(L"0 8 8 8 8 WKE21 BPD10 BKE81 BNF81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 1);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 7, 3 });
//    std::wcin.putback(L'R');
//    game.promotion(figureToMove, Point{ 7, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 7, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"BR");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 17);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from blackArmy set
//    EXPECT_EQ(game.getBlackArmy()->find(figureToMove), game.getBlackArmy()->end());
//
//    ////rook is inserted in blackArmy set
//    EXPECT_NE(game.getBlackArmy()->find(promotedFigure), game.getBlackArmy()->end());
//}
//
//TEST_F(GameTest, rookPromotion2) {
//    // Promotion of black pawn to rook (with exsisting one)
//    game.loadGameDataString(L"0 8 8 8 8 WKE21 BPD10 BKE81 BRF81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 16);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 7, 3 });
//    std::wcin.putback(L'R');
//    game.promotion(figureToMove, Point{ 7, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 7, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"BR");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 48);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from blackArmy set
//    EXPECT_EQ(game.getBlackArmy()->find(figureToMove), game.getBlackArmy()->end());
//
//    ////rook is inserted in blackArmy set
//    EXPECT_NE(game.getBlackArmy()->find(promotedFigure), game.getBlackArmy()->end());
//}
//
//TEST_F(GameTest, bishopPromotion1) {
//    // Promotion of black pawn to bishop (without exsisting one)
//    game.loadGameDataString(L"0 8 8 8 8 WKE21 BPD10 BKE81 BNF81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 1);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 7, 3 });
//    std::wcin.putback(L'B');
//    game.promotion(figureToMove, Point{ 7, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 7, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"BB");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 9);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from blackArmy set
//    EXPECT_EQ(game.getBlackArmy()->find(figureToMove), game.getBlackArmy()->end());
//
//    ////bishop is inserted in blackArmy set
//    EXPECT_NE(game.getBlackArmy()->find(promotedFigure), game.getBlackArmy()->end());
//}
//
//TEST_F(GameTest, bishopPromotion2) {
//    // Promotion of black pawn to bishop (with exsisting one on the same color)
//    game.loadGameDataString(L"0 8 8 8 8 WKE21 BPD10 BKE81 BBG81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 8);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 7, 3 });
//    std::wcin.putback(L'B');
//    game.promotion(figureToMove, Point{ 7, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 7, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"BB");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 8);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from blackArmy set
//    EXPECT_EQ(game.getBlackArmy()->find(figureToMove), game.getBlackArmy()->end());
//
//    ////bishop is inserted in blackArmy set
//    EXPECT_NE(game.getBlackArmy()->find(promotedFigure), game.getBlackArmy()->end());
//}
//
//TEST_F(GameTest, bishopPromotion3) {
//    // Promotion of black pawn to bishop (with exsisting one on the another color)
//    game.loadGameDataString(L"0 8 8 8 8 WKE21 BPD10 BKE81 BBH81");
//
//    ////bitset, converted to UL, before promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 4);
//
//    ////quantity of pawns before promotion
//    EXPECT_EQ(game.getPawnQuantity(), 1);
//
//
//    //// executing promotion
//    Figure* figureToMove = game.getBoard(Point{ 7, 3 });
//    std::wcin.putback(L'B');
//    game.promotion(figureToMove, Point{ 7, 3 });
//    Figure* promotedFigure = game.getBoard(Point{ 7, 3 });
//
//
//    ////type of promoted figure
//    EXPECT_EQ(promotedFigure->getFigureName(), L"BB");
//
//    ////bitset, converted to UL, after promotion
//    EXPECT_EQ(game.getBArmyBit().to_ulong(), 12);
//
//    ////quantity of pawns after promotion
//    EXPECT_EQ(game.getPawnQuantity(), 0);
//
//    ////pawn is erased from blackArmy set
//    EXPECT_EQ(game.getBlackArmy()->find(figureToMove), game.getBlackArmy()->end());
//
//    ////bishop is inserted in blackArmy set
//    EXPECT_NE(game.getBlackArmy()->find(promotedFigure), game.getBlackArmy()->end());
//}
