#include <iostream>
#include <vector>
#include <algorithm>
#include<string>  

#include "board.h"

board::board(std::vector<iPawn*> White, std::vector<iPawn*> Black)
{
    if (White.size() != 5 || Black.size() != 5)
    {
        throw std::invalid_argument("vectors need to contain 5 pawns");
    }
    
	WhitePawns = White;
    BlackPawns = Black;
    
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

bool board::isInTheWay(iPawn *P1, iPawn *P2, iPawn *Ptest)
{
    if(P1->getXPos() * (P2->getYPos() - Ptest->getYPos()) + 
        P2->getXPos() * (Ptest->getYPos() - P1->getYPos()) + 
        Ptest->getXPos() * (P1->getYPos() - P2->getYPos()) == 0)
    {
        int X[] = {P1->getXPos(), P2->getXPos(), Ptest->getXPos()};
        int Y[] = {P1->getYPos(), P2->getYPos(), Ptest->getYPos()};
        std::sort(X, X + 3);
        std::sort(Y, Y + 3);

        if(X[1] == Ptest->getXPos() && Y[1] == Ptest->getYPos())
            return true;
    } 
    return false;
}


bool board::canTransfer(iPawn *P1, iPawn *P2)
{
    // check if pawn is in the same team
    if((std::count(BlackPawns.begin(), BlackPawns.end(), P1) &&
       std::count(WhitePawns.begin(), WhitePawns.end(), P2)) ||
       (std::count(BlackPawns.begin(), BlackPawns.end(), P2) &&
       std::count(WhitePawns.begin(), WhitePawns.end(), P1)) ||
       P1->hasOrb() == P2->hasOrb() || P1 == P2)
    {
       return false;
    }

    // check if pawn is in the way
    for (size_t i = 0; i < WhitePawns.size(); i++)
    {
        if(BlackPawns[i] == P1 || BlackPawns[i] == P2||
            WhitePawns[i] == P1 || WhitePawns[i] == P2)
            continue;
        
        if(isInTheWay(P1, P2, BlackPawns[i]))
            return false;

        if(isInTheWay(P1, P2, WhitePawns[i]))
            return false;
    }

    // check if pawns are linearly aligned

    std::pair<int,int> P1Loc = std::make_pair(P1->getXPos(), P1->getYPos());
    std::pair<int,int> P2Loc = std::make_pair(P2->getXPos(), P2->getYPos());

    if(std::get<1>(P1Loc) == std::get<1>(P2Loc) ||
       std::get<0>(P1Loc) == std::get<0>(P2Loc) ||
       (abs(std::get<0>(P1Loc) - std::get<0>(P2Loc)) ==
       abs(std::get<1>(P1Loc) - std::get<1>(P2Loc))))
        return true;

    return false;
}

bool board::transferOrb(iPawn *P1, iPawn *P2)
{
    if (canTransfer(P1, P2))
    {
        P1->toggleOrb();
        P2->toggleOrb();
        return true;
    }
    return false;
}

////////////////////
//public functions//
////////////////////

bool board::movePawn(iPawn *P, int X, int Y)
{
    for (auto const& item: WhitePawns)
    {
        if (item->getXPos() == X && item->getYPos() == Y)
        {
            if(canTransfer(P, item))
                return transferOrb(P, item);
            else
                return false;
        }
    }

    for (auto const& item: BlackPawns)
    {
        if (item->getXPos() == X && item->getYPos() == Y)
        {
            if(canTransfer(P, item))
                return transferOrb(P, item);
            else
                return false;
        }
    }

    return P->setPosition(X, Y);
}

std::vector<std::pair<int, int>> board::getMoves(iPawn *P)
{
    std::vector<std::pair<int, int>> result;

    if(P->hasOrb())
    {
        for (auto const& item: WhitePawns)
            if(canTransfer(P, item)) 
                result.push_back(std::make_pair(item->getXPos(), item->getYPos()));

        for (auto const& item: BlackPawns)
            if(canTransfer(P, item)) 
                result.push_back(std::make_pair(item->getXPos(), item->getYPos()));

        return result;
    }

    std::vector<std::pair<int,int>> moves = P->getMoves(BOARD_X);
    for (size_t i = 0; i < moves.size(); i++)
    {
        int TestX = P->getXPos() + std::get<0>(moves[i]);
        int TestY = P->getYPos() + std::get<1>(moves[i]);
        int count = 0;

        for (size_t i = 0; i < 5; i++)
        {
            if(TestX < 0 || TestY < 0 || TestX >= BOARD_X || TestY >= BOARD_Y ||
            (TestX == WhitePawns[i]->getXPos() && TestY == WhitePawns[i]->getYPos()) ||
            (TestX == BlackPawns[i]->getXPos() && TestY == BlackPawns[i]->getYPos()))
                count++;
            
        }

        if(count == 0)
            result.push_back(std::make_pair (TestX, TestY));
    }
    
    return result;
}

std::string board::getString(iPawn *P)
{
    std::string output = "\n+---+---+---+---+---+---+---+\n";
    std::vector<std::pair<int, int>> moves;
	std::string white = "\033[37m";
	std::string black = "\033[30m"; 
	std::string def   = "\033[97m";

    if(P != NULL)
        moves = getMoves(P);

    for (int Y = 0; Y < BOARD_Y; Y++)
    {
        output += "|";
        for (int X = 0; X < BOARD_X; X++)
        {
            bool hasPawn = false;

            if(std::count(moves.begin(), moves.end(), std::make_pair(X,Y)))
            {
                auto it = std::find(moves.begin(), moves.end(), std::make_pair(X,Y));
                int index = std::distance(moves.begin(), it);
                output += " " + std::to_string(index) + " |";
                continue;
            }

            for (size_t i = 0; i < WhitePawns.size(); i++)
            {
                if((WhitePawns[i]->getXPos() == X && WhitePawns[i]->getYPos() == Y) || 
                   (BlackPawns[i]->getXPos() == X && BlackPawns[i]->getYPos() == Y))
                {
                    std::string part = "";

                    WhitePawns[i]->getXPos() == X &&
                    WhitePawns[i]->getYPos() == Y ? part += white : part += black;

                    WhitePawns[i]->hasOrb() ? part += " O " : part += " X ";
                    output += part + def +"|";

                    hasPawn = true;
                    break;
                }
            }

            if(!hasPawn)
                output += "   |";

        }
        
        output +="\n+---+---+---+---+---+---+---+\n";
    }

    return output;
}


bool board::checkWin()
{
    for (auto item : WhitePawns)
    {
        if(item->getYPos() == BOARD_Y-1 && item->hasOrb())
            return true;
    }
    
    for (auto item : BlackPawns)
    {
        if(item->getYPos() == 0 && item->hasOrb())
            return true;
    }

    return false;
}
