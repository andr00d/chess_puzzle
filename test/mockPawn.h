#ifndef MPAWN_H
#define MPAWN_H

#include <gmock/gmock.h>
#include "../src/pawn.h"

class mPawn : public pawn
{
    public:
        mPawn(int X, int Y) : pawn(X, Y) {}
        MOCK_METHOD2(setPosition, bool(int x, int y));

        MOCK_METHOD0(getXPos, int());
        MOCK_METHOD0(getYPos, int());

        MOCK_METHOD0(hasOrb, bool());
        MOCK_METHOD0(toggleOrb, void());
        
};

#endif
