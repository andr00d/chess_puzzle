#include <stdexcept>
#include <iostream>
#include <vector>

#include "board.h"

board::board()
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
    return P->setPosition(X, Y);
}
