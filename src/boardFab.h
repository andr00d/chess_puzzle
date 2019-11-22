#ifndef BOARDFAB_H
#define BOARDFAB_H

#include "board.h"

class boardFab
{
    private:

    public:
		virtual ~boardFab() {;}

        //more boardsizes to be added later.
        virtual board *create5x5(std::vector<pawn*> White, std::vector<pawn*> Black)
        {return new board(White, Black);}
};
#endif
