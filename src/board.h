#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "pawn.h"
#define BOARD_SIZE 7

class board
{
    private:

    public:
        board();
		virtual ~board();

		bool transferOrb(pawn P1, pawn P2);
		bool movePawn(pawn P, int X, int Y);
		int checkWin();
		
};
#endif
