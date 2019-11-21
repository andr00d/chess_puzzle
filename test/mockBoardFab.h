#ifndef MBOARDFAB_H
#define MBOARDFAB_H

#include <gmock/gmock.h>
#include "../src/boardFab.h"
#include "../src/board.h"

class mBoardFab : public boardFab
{
    public:       
        MOCK_METHOD2(transferOrb, board(std::vector<pawn*> White, std::vector<pawn*> Black));  
};

#endif
