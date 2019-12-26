#ifndef MKNIGHT_H
#define MKNIGHT_H

#include <gmock/gmock.h>
#include "../src/iPawn.h"

class mKnight : public iPawn
{
    public:
        mKnight(int X, int Y){;}
        MOCK_METHOD2(setPosition, bool(int x, int y));

        MOCK_METHOD0(getXPos, int());
        MOCK_METHOD0(getYPos, int());
        MOCK_METHOD1(getMoves, std::vector<std::pair<int,int>>(unsigned int max));

        MOCK_METHOD0(hasOrb, bool());
        MOCK_METHOD0(toggleOrb, void());
        
};

#endif
