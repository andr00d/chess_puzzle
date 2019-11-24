#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "iBoard.h"
#include "iPawn.h"
#define BOARD_X 7
#define BOARD_Y 7

class board : public iBoard
{
    private:
		virtual bool transferOrb(iPawn *P1, iPawn *P2);
		std::vector<iPawn*> WhitePawns;
		std::vector<iPawn*> BlackPawns;

    public:
        board(std::vector<iPawn*> White, std::vector<iPawn*> Black);
		virtual ~board();

		virtual bool movePawn(iPawn *P, int X, int Y);
		virtual std::vector<std::pair<int, int>> getMoves(iPawn *P);
		virtual bool checkWin();
		virtual std::string getString(iPawn *P = NULL);

		virtual std::vector<iPawn*> getWhitePawns(){return WhitePawns;}
		virtual std::vector<iPawn*> getBlackPawns(){return BlackPawns;}	
};
#endif
