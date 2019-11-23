#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "gameHandler.h"
#include "board.h"

gameHandler::gameHandler(boardFab *BF, pawnFab *PF)
{
	std::vector<iPawn*> WhitePawns;
    std::vector<iPawn*> BlackPawns; 

    for (size_t i = 0; i < 5; i++)
    {
        WhitePawns.push_back(PF->createPawn());
        BlackPawns.push_back(PF->createPawn());
    }
    
    B = BF->create5x5(WhitePawns, BlackPawns);
    isWhiteTurn = true;
}

gameHandler::~gameHandler()
{
    delete B;
    B = NULL;    
}

/////////////////////
//private functions//
/////////////////////


////////////////////
//public functions//
////////////////////

gameState gameHandler::makeTurn(iPawn *P, int X, int Y)
{   
    std::vector<iPawn*> pwns = B->getWhitePawns();
    bool isPwnWhite = std::count(pwns.begin(), pwns.end(), P);

    if(isPwnWhite != isWhiteTurn)
        return INVALID_MOVE;

    if(B->movePawn(P, X, Y))
    {
        if(B->checkWin())
        {
            if(isWhiteTurn)
                return WHITE_WON;
            else
                return BLACK_WON;
        }

        isWhiteTurn = !isWhiteTurn;
        return VALID_MOVE;
    }
    
    return INVALID_MOVE;
}

std::vector<iPawn*> gameHandler::getMoveAblePawns()
{
    std::vector<iPawn*> MoveablePawns;

    for (auto item : B->getWhitePawns())
    {
        if(B->getMoves(item).size() > 0)
            MoveablePawns.push_back(item);
    }
    
    return MoveablePawns;
}