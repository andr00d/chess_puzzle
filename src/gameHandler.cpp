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
    bool isPwnWhite = std::find(B->getWhitePawns().begin(),
                      B->getWhitePawns().end(), P) != B->getWhitePawns().end();

    if(isPwnWhite != isWhiteTurn)
        return INVALID_MOVE;

    if(B->movePawn(P, X, Y))
    {
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