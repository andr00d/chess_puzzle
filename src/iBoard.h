#ifndef IBOARD_H
#define IBOARD_H

#include <vector>
#include "iPawn.h"
#define BOARD_SIZE 7

class iBoard
{
    public:
		virtual ~iBoard(){;}

		virtual bool transferOrb(iPawn *P1, iPawn *P2) = 0;
		virtual bool movePawn(iPawn *P, int X, int Y) = 0;
		virtual std::vector<std::pair<int, int>> getMoves(iPawn *P) = 0;
		virtual std::vector<iPawn*> getWhitePawns() = 0;
		virtual std::vector<iPawn*> getBlackPawns() = 0;
		virtual std::string getString() = 0;
		virtual bool checkWin() = 0;
		
};
#endif
