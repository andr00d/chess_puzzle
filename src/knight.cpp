#include <stdexcept>
#include <algorithm>
#include "knight.h"

#define getX std::get<0>
#define getY std::get<1>

knight::knight(int X, int Y)
{
	XPos = X;
	YPos = Y;
	HasOrb = false;
}

knight::~knight()
{
	
}

/////////////////////
//private functions//
/////////////////////



////////////////////
//public functions//
////////////////////

bool knight::setPosition(int x, int y)
{
	if( x < 0 || y < 0)
		return false;

	// All possible moves of a knight 
	bool possible = false;

	for (auto move : getMoves(0))
	{
		if(getX(move) + XPos == x && getY(move) + YPos == y)
			possible = true;
	}
	
	if(!possible)
		return false;

	XPos = x;
	YPos = y;
	return true;
}


std::vector<std::pair<int,int>> knight::getMoves(unsigned int max)
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