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

bool board::transferOrb(iPawn *P1, iPawn *P2)
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

////////////////////
//public functions//
////////////////////

bool board::movePawn(iPawn *P, int X, int Y)
{

    for (auto const& item: WhitePawns)
    {
        if (item->getXPos() == X && item->getYPos() == Y)
            return transferOrb(P, item);
    }

    for (auto const& item: BlackPawns)
    {
        if (item->getXPos() == X && item->getYPos() == Y)
            return transferOrb(P, item);
    }

    return P->setPosition(X, Y);
}

std::vector<std::pair<int, int>> board::getMoves(iPawn *P)
{
    std::vector<std::pair<int, int>> result;
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
