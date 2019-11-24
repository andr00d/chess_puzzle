#ifndef PAWNFAB_H
#define PAWNFAB_H

#include "pawn.h"

class pawnFab
{
    private:

    public:
		virtual ~pawnFab() {;}

    //more pawns to be added later.
    virtual iPawn *createPawn(int X, int Y){return new pawn(X, Y);}
};
#endif
