#include <stdexcept>
#include <iostream>

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

std::vector<iPawn*> gameHandler::getMoveAblePawns()
{
    std::vector<iPawn*> MoveablePawns;
    return MoveablePawns;
}