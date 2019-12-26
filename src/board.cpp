#include <iostream>
#include <vector>
#include <algorithm>
#include<string>  

#include "board.h"
#define getX std::get<0>
#define getY std::get<1>

board::board(std::vector<iPawn*> White, std::vector<iPawn*> Black)
{
    if (White.size() != NR_PAWNS || Black.size() != NR_PAWNS)
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
	for (auto item : GetAllPawns())
        delete item;
}

/////////////////////
//private functions//
/////////////////////

std::vector<iPawn*> board::GetAllPawns()
{
    std::vector<iPawn*> result;
    for (auto item : WhitePawns)
        result.push_back(item);

    for (auto item : BlackPawns)
        result.push_back(item);
    
    return result;
}

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

        // make sure PTest is in the middle
        std::cout <<"testing in middle" << std::endl;
        std::cout << Ptest->getXPos() << " - " << Ptest->getYPos() << std::endl;
        std::cout << X[1] << " - " << Y[1] << std::endl;
        if(X[1] == Ptest->getXPos() && Y[1] == Ptest->getYPos())
            return true;
    } 
    return false;
}


bool board::canTransfer(iPawn *P1, iPawn *P2)
{
    // check if pawn is in the same team, or are the same
    if((std::count(BlackPawns.begin(), BlackPawns.end(), P1) &&
       std::count(WhitePawns.begin(), WhitePawns.end(), P2)) ||
       (std::count(BlackPawns.begin(), BlackPawns.end(), P2) &&
       std::count(WhitePawns.begin(), WhitePawns.end(), P1)) ||
       P1->hasOrb() == P2->hasOrb() || P1 == P2)
    {
       return false;
    }

    // check if a pawn is in the way
    for (auto item : GetAllPawns())
    {
        if(item == P1 || item == P2)
            continue;
          
        if(isInTheWay(P1, P2, item))
            return false;  
    }

    // check if P2 is in a transferable location
    std::vector<std::pair<int,int>> passLoc = P1->getMoves(BOARD_X);
    std::pair<int,int> P1Loc = std::make_pair(P1->getXPos(), P1->getYPos());
    std::pair<int,int> P2Loc = std::make_pair(P2->getXPos(), P2->getYPos());
    for (auto item : passLoc)
        if(getX(P1Loc) + getX(item) == getX(P2Loc) && getY(P1Loc) + getY(item) == getY(P2Loc))
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
    for (auto const& item: GetAllPawns())
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
        for (auto const& item: GetAllPawns())
            if(canTransfer(P, item)) 
                result.push_back(std::make_pair(item->getXPos(), item->getYPos()));
        
        return result;
    }

    std::vector<std::pair<int,int>> moves = P->getMoves(BOARD_X);
    for (size_t i = 0; i < moves.size(); i++)
    {
        int TestX = P->getXPos() + getX(moves[i]);
        int TestY = P->getYPos() + getY(moves[i]);
        int count = 0;

        for (auto item : GetAllPawns())
        {
            if(TestX < 0 || TestY < 0 || TestX >= BOARD_X || TestY >= BOARD_Y ||
            (TestX == item->getXPos() && TestY == item->getYPos()))
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
            
            for (auto item : GetAllPawns())
            {
                if(item->getXPos() == X && item->getYPos() == Y)
                {
                    std::string part = "";
                    std::count(WhitePawns.begin(), WhitePawns.end(), item) ? part += white : part += black;
                    item->hasOrb() ? part += " O " : part += " X ";
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
