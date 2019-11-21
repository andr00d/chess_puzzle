#ifndef MPAWNFAB_H
#define MPAWNFAB_H

#include <gmock/gmock.h>
#include "../src/pawnFab.h"
#include "../src/pawn.h"

class mPawnFab : public pawnFab
{
    public:       
        MOCK_METHOD2(getPawn, pawn(int X, int Y));  
};

#endif
