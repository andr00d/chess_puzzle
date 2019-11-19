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
		return false;

	// All possible moves of a knight 
	bool possible = false;
	int TryX[] = {-2, -2, -1, 2, 1, -1, 1, 2}; 
	int TryY[] = {1, -1, -2, 1, 2, 2, -2, -1}; 

	for (int i = 0; i < 8; i++)
	{
		if(XPos + TryX[i] == x && YPos + TryY[i] == y)
		   	possible = true;
	}
	
	if(!possible)
		return false;

	XPos = x;
	YPos = y;
	return true;
}

void pawn::toggleOrb()
{
	HasOrb = !HasOrb;
}