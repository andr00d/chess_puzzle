#ifndef BOARDFAB_H
#define BOARDFAB_H

#include "board.h"

class boardFab
{
    private:

    public:
        //more boardsizes to be added later.
        board *Create5x5(std::vector<pawn*> White, std::vector<pawn*> Black)
        {return new board(White, Black);}
};
#endif
