#ifndef MPAWN_H
#define MPAWN_H

#include <gmock/gmock.h>
#include "../src/iPawn.h"

class mPawn : public iPawn
{
    public:
        mPawn(int X, int Y){;}
        MOCK_METHOD2(setPosition, bool(int x, int y));

        MOCK_METHOD0(getXPos, int());
        MOCK_METHOD0(getYPos, int());

        MOCK_METHOD0(hasOrb, bool());
        MOCK_METHOD0(toggleOrb, void());
        
};

#endif
