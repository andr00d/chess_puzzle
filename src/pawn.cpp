#include <stdexcept>

#include "pawn.h"

pawn::pawn()
{
	XPos = 0;
	YPos = 0;
	HasOrb = false;
}

pawn::~pawn()
{
	
}

/////////////////////
//private functions//
/////////////////////



////////////////////
//public functions//
////////////////////

bool pawn::setPosition(int x, int y)
{
	if( x < 0 || y < 0)
	{
		return false;
	}

	XPos = x;
	YPos = y;
	return true;
}

void pawn::toggleOrb()
{
	HasOrb = !HasOrb;
}