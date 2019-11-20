#include <stdexcept>
#include <iostream>
#include <vector>

#include "board.h"

board::board(std::vector<pawn*> Pawnlist)
{
	Pawns = Pawnlist;
}

board::~board()
{
	
}

/////////////////////
//private functions//
/////////////////////

////////////////////
//public functions//
////////////////////

bool board::movePawn(pawn *P, int X, int Y)
{
    std::cout << Pawns.size() << std::endl;
    for (auto const& item: Pawns)
    {
        if (item->getXPos() == X && item->getYPos() == Y)
            return false;
    }
    
    return P->setPosition(X, Y);
}

bool board::transferOrb(pawn *P1, pawn *P2)
{
    if (P1->getXPos() == P2->getXPos() || 
        P1->getYPos() == P2->getYPos() ||
        P1->getXPos() - P2->getXPos() == 
        P1->getYPos() - P2->getYPos())
    {
        for (auto const& item: Pawns)
        {
            if(item == P1 || item == P2)
                continue;

            // check if a pawn is in the way
            if(P1->getXPos() * (P2->getYPos() - item->getYPos()) + 
               P2->getXPos() * (item->getYPos() - P1->getYPos()) + 
               item->getXPos() * (P1->getYPos() - P2->getYPos()) == 0 &&
               item->getYPos() >= P1->getYPos() && item->getYPos() <= P2->getYPos() &&
               item->getXPos() >= P1->getXPos() && item->getXPos() <= P2->getXPos())
            {
                return false;
            }
        }

        P1->toggleOrb();
        P2->toggleOrb();
        return true;
    }

    return false;
}