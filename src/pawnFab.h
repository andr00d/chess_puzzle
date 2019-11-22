#ifndef PAWNFAB_H
#define PAWNFAB_H

#include "pawn.h"

class pawnFab
{
    private:

    public:
		virtual ~pawnFab() {;}

        //more pawns to be added later.
        virtual iPawn *createPawn(){return new pawn(0,0);}
};
#endif
