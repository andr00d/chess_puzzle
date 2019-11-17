#include <stdexcept>

#include "pawn.h"

pawn::pawn()
{
	XPos = 0;
	yPos = 0;
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

void pawn::setPosition(int x, int y)
{

	XPos = x;
	yPos = y;
}