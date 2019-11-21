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

    public:
        gameHandler(boardFab *B, pawnFab *fab);
		virtual ~gameHandler();
		
		gameState makeTurn(pawn *P, int X, int Y);
        std::vector<pawn*> getMoveAblePawns();
};
#endif
