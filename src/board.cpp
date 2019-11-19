#include <stdexcept>
#include <iostream>
#include <vector>

#include "board.h"

board::board(std::vector<pawn> Pawns)
{
	
}

board::~board()
{
	
}

/////////////////////
//private functions//
/////////////////////

////////////////////
//public functions//
////////////////////

bool board::movePawn(pawn *P, int X, int Y)
{
    for (auto item: Pawns)
    {
        if (item.getXPos() == X && item.getYPos() == Y)
            return false;
    }
    
    return P->setPosition(X, Y);
}
