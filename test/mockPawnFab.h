#ifndef MPAWNFAB_H
#define MPAWNFAB_H

#include <gmock/gmock.h>
#include "../src/pawnFab.h"
#include "../src/iPawn.h"

class mPawnFab : public pawnFab
{
    public:     
        ~mPawnFab(){;}

        MOCK_METHOD2(createPawn, iPawn*(int X, int Y));  
};

#endif
