#ifndef MBOARD_H
#define MBOARD_H

#include <gmock/gmock.h>
#include "../src/iBoard.h"
#include "../src/iPawn.h"

class mBoard : public iBoard
{
    public:
        mBoard(std::vector<iPawn*> White, std::vector<iPawn*> Black){;}
       
        MOCK_METHOD2(transferOrb, bool(iPawn *P1, iPawn *P2));
        MOCK_METHOD3(movePawn, bool(iPawn *P1, int X, int Y));
        MOCK_METHOD1(getMoves, std::vector<std::pair<int, int>>(iPawn *P1));

        MOCK_METHOD0(getWhitePawns, std::vector<iPawn*>());
        MOCK_METHOD0(getBlackPawns, std::vector<iPawn*>());

        MOCK_METHOD0(checkWin, bool());       
};

#endif
