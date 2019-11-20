#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "pawn.h"
#define BOARD_SIZE 7

class board
{
    private:
		std::vector<pawn*> WhitePawns;
		std::vector<pawn*> BlackPawns;

    public:
        board(std::vector<pawn*> White, std::vector<pawn*> Black);
		virtual ~board();

		bool transferOrb(pawn *P1, pawn *P2);
		bool movePawn(pawn *P, int X, int Y);
		int checkWin();
		
};
#endif
