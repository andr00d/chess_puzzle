#ifndef MBOARDFAB_H
#define MBOARDFAB_H

#include <gmock/gmock.h>
#include "../src/boardFab.h"
#include "../src/board.h"
#include "../src/pawn.h"

class mBoardFab : public boardFab
{
    public:     
        ~mBoardFab(){;}

        MOCK_METHOD2(create5x5, board*(std::vector<pawn*> White, std::vector<pawn*> Black));  
};

#endif
