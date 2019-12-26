#ifndef PAWNFAB_H
#define PAWNFAB_H

#include "knight.h"

class pawnFab
{
    private:

    public:
		virtual ~pawnFab() {;}

    //more pawns to be added later.
    virtual iPawn *createPawn(int X, int Y){return new knight(X, Y);}
};
#endif
