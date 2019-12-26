#ifndef PAWN_KNIGHT_H
#define PAWN_KNIGHT_H

#include <vector>
#include "iPawn.h"

class knight : public iPawn
{
    private:
		int XPos;
		int YPos;
		bool HasOrb;

    public:
        knight(int X, int Y);
		virtual ~knight();

		virtual bool setPosition(int x, int y);
		virtual int getXPos(){return XPos;}
		virtual int getYPos(){return YPos;}
		virtual std::vector<std::pair<int,int>> getMoves(unsigned int max);
		
		virtual bool hasOrb(){return HasOrb;}
		virtual void toggleOrb(){HasOrb = !HasOrb;}
};
#endif
