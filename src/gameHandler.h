#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "gameState.h"
#include "boardFab.h"
#include "pawnFab.h"
#include "iBoard.h"
#include "iPawn.h"

class gameHandler
{
    private:
        iBoard *B;

        bool isWhiteTurn;

    public:
        gameHandler(boardFab *BF, pawnFab *PF);
		virtual ~gameHandler();
		
		gameState makeTurn(iPawn *P, int X, int Y);
        std::vector<iPawn*> getMoveAblePawns();
};
#endif
