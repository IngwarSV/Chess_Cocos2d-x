#include "MyTests.h"

bool MyTests::TestIsCheck() {
    // WK is in check under attack by BQ
    _core->loadData("1 0 0 8 8 8 8", "WKA80", "BQA50 BKC40", "");
    bool flag1 = _core->isCheck();

    // WK is not in check
    _core->loadData("1 8 8 8 8", "WKB80", "BQA50 BKC40", "");
    bool flag2f = _core->isCheck();

    return flag1 && !flag2f;
}

bool MyTests::TestIsCheckmate() {
    // Black king is checkmated with a rook
    _core->loadData("0 0 0 8 8 8 8", "WKF5 WRH1", "BKH5", "");
    bool flag1 = _core->isCheckmate();

    // Black king is not checkmated with a rook, black knight can cover black king
    _core->loadData("0 0 0 8 8 8 8", "WKF5 WRH1", "BNG2 BKH5", "");
    bool flag2f = _core->isCheckmate();

    // Black king is checkmated with a bishop and a knight
    _core->loadData("0 0 0 8 8 8 8", "WKG6 WBF6 WNH6", "BKH8", "");
    bool flag3 = _core->isCheckmate();

    // Black king is not checkmated with a bishop and a knight, black rook can attack white bishop
    _core->loadData("0 0 0 8 8 8 8", "WKG6 WBF6 WNH6", "BRA6 BKH8", "");
    bool flag4f = _core->isCheckmate();

    // checking if enPassant can be performed to protect the king
    //// Black pawn, which has just advanced for two squares, checkmates the white king
    _core->loadData("1 0 0 4 1 5 1", "WKA4 BNC6", "BRH3 BKE8 BPB5 BQB8", "");
    bool flag5 = _core->isCheckmate();

    //// Black pawn, which has just advanced for two squares, can be captured en passant by white pawn
    _core->loadData("1 0 0 4 1 5 1", "WKA4 WPC5", "BNC6 BRH3 BKE8 BPB5 BQB8", "");
    bool flag6f = _core->isCheckmate();

    return flag1 && !flag2f && flag3 && !flag4f && flag5 && !flag6f;
}

bool MyTests::TestIsDraw() {
    // checking stalemate
    ////Black are in stalemate
    _core->loadData("0 0 0 8 8 8 8", "WKF7 WQG6 WPB2 WPC3", "BPB3 BKH8", "");
    bool flag1 = _core->isDraw();

    ////Black are not in stalemate, because of en passant move
    _core->loadData("0 0 0 2 2 1 2", "WKF7 WQG6 WPB2 WPC3", "BPB3 BKH8", "");
    bool flag2f = _core->isDraw();

    // checking impossibility of checkmate
    //// two kings left
    _core->loadData("0 0 0 8 8 8 8", "WKF7", "BKH8", "");
    bool flag3 = _core->isDraw();

    //// two kings and one white pawn left
    _core->loadData("0 0 0 8 8 8 8", "WKF7 WPB5", "BKH8", "");
    bool flag4f = _core->isDraw();

    //// two kings and one black pawn left
    _core->loadData("0 0 0 8 8 8 8", "WKF7", "BPB5 BKH8", "");
    bool flag5f = _core->isDraw();

    //// king with/without bishop versus king and bishop(bishops) on the same color
    //// king versus king and bishop
    _core->loadData("0 0 0 8 8 8 8", "WKF7 WBB5", "BKH8", "");
    bool flag6 = _core->isDraw();

    //// king versus king and bishops on the same color
    _core->loadData("0 0 0 8 8 8 8", "WKF7 WBB5 WBC6", "BKH8", "");
    bool flag7 = _core->isDraw();

    //// king with bishop versus king and bishops on the same color
    _core->loadData("0 0 0 8 8 8 8", "WKF7 WBB5 WBC6", "BKH8 BBD5", "");
    bool flag8 = _core->isDraw();

    //// king with bishop versus king and bishops on the different colors
    _core->loadData("0 0 0 8 8 8 8", "WKF7 WBB5 WBC6", "BKH8 BBD4", "");
    bool flag9f = _core->isDraw();

    //// king and knight versus king
    _core->loadData("0 0 0 8 8 8 8", "WKF7", "BKH8 BND5", "");
    bool flag10 = _core->isDraw();


    return flag1 && !flag2f && flag3 && !flag4f && !flag5f && flag6 && flag7 && flag8 && !flag9f && flag10;
}

bool MyTests::TestÑastling() {
    // cheking for castling, no restrictions

     //// white king with kingside rook
    _core->loadData("1 0 0 8 8 8 8", "WKE11 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag1 = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,6 });

    //// black king with kingside rook
    _core->loadData("0 0 0 8 8 8 8", "WKE11 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag2 = _core->castling(_core->getActiveKing(), Location{ 7,4 }, Location{ 7,6 });

    //// white king with queenside rook
    _core->loadData("1 0 0 8 8 8 8", "WKE11 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag3 = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    //// black king with queenside rook
    _core->loadData("0 0 0 8 8 8 8", "WKE11 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag4 = _core->castling(_core->getActiveKing(), Location{ 7,4 }, Location{ 7,2 });


    // cheking for castling, king is under attack

    //// white king is under attack
    _core->loadData("1 0 0 8 8 8 8", "WKE11 WRH11 WRA11", "BKE81 BRE70 BRA81", "");
    bool flag5f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    //// black king is under attack
    _core->loadData("0 0 0 8 8 8 8", "WKE11 WRE20 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag6f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });


    // cheking for castling, rook has moved before

    //// white king with kingside rook
    _core->loadData("1 0 0 8 8 8 8", "WKE11 WRH10 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag7f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,6 });

    //// black king with kingside rook
    _core->loadData("0 0 0 8 8 8 8", "WKE11 WRH11 WRA11", "BKE81 BRH80 BRA81", "");
    bool flag8f = _core->castling(_core->getActiveKing(), Location{ 7,4 }, Location{ 7,6 });

    //// white king with queenside rook
    _core->loadData("1 0 0 8 8 8 8", "WKE11 WRH11 WRA10", "BKE81 BRH81 BRA81", "");
    bool flag9f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    //// black king with queenside rook
    _core->loadData("0 0 0 8 8 8 8", "WKE11 WRH11 WRA11", "BKE81 BRH81 BRA80", "");
    bool flag10f = _core->castling(_core->getActiveKing(), Location{ 7,4 }, Location{ 7,2 });


    // cheking for castling, king has moved before

    //// white king with kingside rook
    _core->loadData("1 0 0 8 8 8 8", "WKE10 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag11f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,6 });

    //// black king with kingside rook
    _core->loadData("0 0 0 8 8 8 8", "WKE11 WRH11 WRA11", "BKE80 BRH81 BRA81", "");
    bool flag12f = _core->castling(_core->getActiveKing(), Location{ 7,4 }, Location{ 7,6 });


    // cheking for castling, squares between king and rook are not empty
    _core->loadData("1 0 0 8 8 8 8", "WKE10 WBB1 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag13f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    _core->loadData("1 0 0 8 8 8 8", "WKE10 WBC1 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag14f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    _core->loadData("1 0 0 8 8 8 8", "WKE10 WBD1 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag15f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    _core->loadData("1 0 0 8 8 8 8", "WKE10 WBF1 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag16f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,6 });

    _core->loadData("1 0 0 8 8 8 8", "WKE10 WBG1 WRH11 WRA11", "BKE81 BRH81 BRA81", "");
    bool flag17f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,6 });

    // cheking for castling, squares between king and rook are under attack
    _core->loadData("1 0 0 8 8 8 8", "WKE10 WRH11 WRA11", "BKE81 BRH81 BRA81 BQB8", "");
    bool flag18f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    _core->loadData("1 0 0 8 8 8 8", "WKE10 WRH11 WRA11", "BKE81 BRH81 BRA81 BQC8", "");
    bool flag19f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    _core->loadData("1 0 0 8 8 8 8", "WKE10 WRH11 WRA11", "BKE81 BRH81 BRA81 BQD8", "");
    bool flag20f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,2 });

    _core->loadData("1 0 0 8 8 8 8", "WKE10 WRH11 WRA11", "BKE81 BRH81 BRA81 BQF8", "");
    bool flag21f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,6 });

    _core->loadData("1 0 0 8 8 8 8", "WKE10 WRH11 WRA11", "BKE81 BRH81 BRA81 BQG8", "");
    bool flag22f = _core->castling(_core->getActiveKing(), Location{ 0,4 }, Location{ 0,6 });

    return flag1 && flag2 && flag3 && flag4 && !flag5f && !flag6f && !flag7f && !flag8f &&
        !flag9f && !flag10f && !flag11f && !flag12f && !flag13f && !flag14f && !flag15f &&
        !flag16f && !flag17f && !flag18f && !flag19f && !flag20f && !flag21f && !flag22f;
}

bool MyTests::TestEnPassant() {
    // cheking for enPassant, no restriction
    _core->loadData("1 0 0 4 1 5 1", "WKC10 WPC50", "BKB80 BPB50", "");
    Figure* figureToMove = _core->getFigureOnBoard(Location{ 4, 2 });

    bool flag1 = _core->enPassant(figureToMove, Location{ 4,2 }, Location{ 5,1 });

    _core->loadData("0 0 0 2 2 1 2", "WKC10 WPC30", "BKB80 BPB30", "");
    figureToMove = _core->getFigureOnBoard(Location{ 2, 1 });

    bool flag2 = _core->enPassant(figureToMove, Location{ 2,1 }, Location{ 1,2 });

    // cheking for enPassant, king is under attack in case enPassant
    _core->loadData("1 0 0 4 1 5 1", "WKC10 WPC50", "BKB80 BPB50 BRC80", "");
    figureToMove = _core->getFigureOnBoard(Location{ 4, 2 });

    bool flag3f = _core->enPassant(figureToMove, Location{ 4,2 }, Location{ 5,1 });

    _core->loadData("0 0 0 2 2 1 2", "WKC10 WPC30 WRB10", "BKB80 BPB30", "");
    figureToMove = _core->getFigureOnBoard(Location{ 2, 1 });

    bool flag4f = _core->enPassant(figureToMove, Location{ 2,1 }, Location{ 1,2 });

    return flag1 && flag2 && !flag3f && !flag4f;
}

bool MyTests::TestIsKingInDanger() {
    // King is not attacked due to the movement of the figure

    //// white pawn moves
    _core->loadData("1 0 0 8 8 8 8", "WKE11 WPD21", "BKE81 BBF81", "");
    Figure* figureToMove = _core->getFigureOnBoard(Location{ 1, 3 });

    bool flag1f = _core->isKingInDanger(figureToMove, Location{ 1,3 }, Location{ 3,3 });

    //// black bishop moves
    _core->loadData("0 0 0 8 8 8 8", "WKE11 WPD21", "BKE81 BBF81", "");
    figureToMove = _core->getFigureOnBoard(Location{ 7, 5 });

    bool flag2f = _core->isKingInDanger(figureToMove, Location{ 7,5 }, Location{ 6,4 });


    // King is attacked due to the movement of the figure

    //// white pawn moves, king is under attack of black bishop
    _core->loadData("1 0 0 8 8 8 8", "WKE11 WPD21", "BKE81 BBF81 BBA50", "");
    figureToMove = _core->getFigureOnBoard(Location{ 1, 3 });

    bool flag3 = _core->isKingInDanger(figureToMove, Location{ 1,3 }, Location{ 3,3 });

    //// black bishop moves, king is under attack of white rook
    _core->loadData("0 0 0 8 8 8 8", "WKE11 WPD21 WRH80", "BKE81 BBF81", "");
    figureToMove = _core->getFigureOnBoard(Location{ 7, 5 });

    bool flag4 = _core->isKingInDanger(figureToMove, Location{ 7,5 }, Location{ 6,4 });

    // King is attacked due to his movement
    //// White king is under attack in case of movement
    _core->loadData("1 0 0 8 8 8 8", "WKF10", "BKE81 BBF81 BBA50", "");
    figureToMove = _core->getFigureOnBoard(Location{ 0, 5 });

    bool flag5 = _core->isKingInDanger(figureToMove, Location{ 0,5 }, Location{ 0,4 });

    //// Black king is under attack in case of movement
    _core->loadData("0 0 0 8 8 8 8", "WKF10", "BKE71 WRH80", "");
    figureToMove = _core->getFigureOnBoard(Location{ 6, 4 });

    bool flag6 = _core->isKingInDanger(figureToMove, Location{ 6,4 }, Location{ 7,4 });

    return !flag1f && !flag2f && flag3 && flag4 && flag5 && flag6;
}



void MyTests::runCoreTests()
{
    bool allTestPassed = true;
    _core->_testsResults.push_back("Tests failed: ");
   
    //TestIsCheck()
    if (!TestIsCheck()) { _core->_testsResults.push_back("\tTestIsCheck()"); allTestPassed = false; }

    //TestIsCheckmate()
    if (!TestIsCheckmate()) { _core->_testsResults.push_back("\tTestIsCheckmate()"); allTestPassed = false; }

    //TestIsDraw()
    if (!TestIsDraw()) { _core->_testsResults.push_back("\tTestIsDraw()"); allTestPassed = false; }
    
    //TestÑastling()
    if (!TestÑastling()) { _core->_testsResults.push_back("\tTestCastling()"); allTestPassed = false; }
    
    //TestEnPassant()
    if (!TestEnPassant()) { _core->_testsResults.push_back("\tTestEnPassant()"); allTestPassed = false; }
  
    //TestIsKingInDanger()
    if (!TestIsKingInDanger()) { _core->_testsResults.push_back("\tTestIsKingInDanger()"); allTestPassed = false; }


    
    if (allTestPassed) {
        _core->_testsResults.back() += "0";
    }
    _core->clearData();
    _core->initialSetup();
}
