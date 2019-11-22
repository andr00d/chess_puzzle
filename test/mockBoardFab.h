#ifndef MBOARDFAB_H
#define MBOARDFAB_H

#include <gmock/gmock.h>
#include <iostream>
#include "../src/boardFab.h"
#include "../src/iBoard.h"
#include "../src/iPawn.h"

class mBoardFab : public boardFab
{
    public:     
        ~mBoardFab(){;}

        MOCK_METHOD2(create5x5, iBoard*(std::vector<iPawn*> White, std::vector<iPawn*> Black));
};

#endif
