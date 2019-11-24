#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "iPawn.h"

class pawn : public iPawn
{
    private:
		int XPos;
		int YPos;
		bool HasOrb;

    public:
        pawn(int X, int Y);
		virtual ~pawn();

		virtual bool setPosition(int x, int y);
		virtual int getXPos(){return XPos;}
		virtual int getYPos(){return YPos;}
		virtual std::vector<std::pair<int,int>> getMoves(unsigned int max);
		
		virtual bool hasOrb(){return HasOrb;}
		virtual void toggleOrb();
};
#endif
