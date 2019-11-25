#ifndef BOARDFAB_H
#define BOARDFAB_H

#include "board.h"

class boardFab
{
    private:

    public:
		virtual ~boardFab() {;}

        //more boardsizes to be added later.
        virtual iBoard *create7x7(std::vector<iPawn*> White, std::vector<iPawn*> Black)
        {return new board(White, Black);}
};
#endif
