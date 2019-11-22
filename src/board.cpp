#include <stdexcept>
#include <iostream>
#include <vector>

#include "board.h"

board::board(std::vector<pawn*> White, std::vector<pawn*> Black)
{
    if (White.size() != 5 || Black.size() != 5)
    {
        throw std::invalid_argument("vectors need to contain 5 pawns");
    }
    
	WhitePawns = White;
    BlackPawns = Black;

    for (size_t i = 0; i < WhitePawns.size(); i++)
    {
        WhitePawns[i]->setPosition(i+1, 0);
        BlackPawns[i]->setPosition(i+1, 6);
    }
    
    WhitePawns[2]->toggleOrb();
    BlackPawns[2]->toggleOrb();
}

board::~board()
{
	for (auto item : WhitePawns)
        delete item;
       
    for (auto item : BlackPawns)
        delete item;
}

/////////////////////
//private functions//
/////////////////////

////////////////////
//public functions//
////////////////////

bool board::movePawn(pawn *P, int X, int Y)
{
    for (auto const& item: WhitePawns)
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
        for (auto const& item: WhitePawns)
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

std::vector<std::pair<int, int>> board::GetMoves(pawn *P)
{
    std::vector<std::pair<int, int>> result;
    int steps[][2] = {{-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}, {-2,1}};

    for (int i = 0; i < 8; i++)
    {
        int TestX = P->getXPos() + steps[i][0];
        int TestY = P->getYPos() + steps[i][1];
        int count = 0;

        for (size_t i = 0; i < 5; i++)
        {
            if(TestX < 0 || TestY < 0 || 
            (TestX == WhitePawns[i]->getXPos() && TestY == WhitePawns[i]->getYPos()) ||
            (TestX == BlackPawns[i]->getXPos() && TestY == BlackPawns[i]->getYPos()))
                count++;
            
        }

        if(count == 0)
            result.push_back(std::make_pair (TestX, TestY));
    }
    
    return result;
}

bool board::checkWin()
{
    return false;
}