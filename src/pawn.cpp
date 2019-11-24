#include <stdexcept>

#include "pawn.h"

pawn::pawn(int X, int Y)
{
	XPos = X;
	YPos = Y;
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


std::vector<std::pair<int,int>> pawn::getMoves(unsigned int max)
{
	std::vector<std::pair<int,int>> moves;

	if(!HasOrb)
	{
		int steps[][2] = {{-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}, {-2,1}};
		for (int i = 0; i < 8; i++)
			moves.push_back(std::make_pair(steps[i][0], steps[i][1]));
		
		return moves;
	}

	if(max > 0)
	{
		for (size_t i = 1; i <= max; i++)
		{
			moves.push_back(std::make_pair(i,  0));
			moves.push_back(std::make_pair(-i, 0));
			moves.push_back(std::make_pair(0,  i));
			moves.push_back(std::make_pair(0, -i));
			moves.push_back(std::make_pair(i,  i));
			moves.push_back(std::make_pair(i, -i));
			moves.push_back(std::make_pair(-i, i));
			moves.push_back(std::make_pair(-i,-i));
		}
	}

	return moves;
}

void pawn::toggleOrb()
{
	HasOrb = !HasOrb;
}