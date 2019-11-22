#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "gameState.h"
#include "boardFab.h"
#include "pawnFab.h"
#include "board.h"
#include "pawn.h"

class gameHandler
{
    private:
        iBoard *B;

    public:
        gameHandler(boardFab *BF, pawnFab *PF);
		virtual ~gameHandler();
		
		gameState makeTurn(pawn *P, int X, int Y);
        std::vector<iPawn*> getMoveAblePawns();
};
#endif
