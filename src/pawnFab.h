#ifndef PAWNFAB_H
#define PAWNFAB_H

#include "pawn.h"

class pawnFab
{
    private:

    public:
        //more pawns to be added later.
        pawn *getPawn(){return new pawn(0,0);}
};
#endif