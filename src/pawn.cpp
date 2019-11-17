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
	if( x < 0 || y < 0)
	{
		throw std::invalid_argument("position cannot be negative");
	}

	XPos = x;
	yPos = y;
}