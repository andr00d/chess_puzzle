#ifndef MBOARD_H
#define MBOARD_H

#include <gmock/gmock.h>
#include "../src/board.h"
#include "../src/pawn.h"

class mBoard : public board
{
    public:
        mBoard(std::vector<pawn*> White, std::vector<pawn*> Black) : board(White, Black) {}
       
        MOCK_METHOD2(transferOrb, bool(pawn P1, pawn P2));
        MOCK_METHOD3(movePawn, bool(pawn P1, int X, int Y));
        MOCK_METHOD1(GetMoves, std::vector<std::pair<int, int>>(pawn P1));
        MOCK_METHOD0(checkWin, bool());       
};

#endif
