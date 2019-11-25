#include <iostream>
#include <string>
#include <vector>
#include <utility> 

#include "gameHandler.h"
#include "gameState.h"
#include "boardFab.h"
#include "pawnFab.h"


int inputresult(std::string message)
{
	std::cout << message << std::endl;
	int index = '\0';
	std::cin >> index;
	std::cin.ignore();

	return index;
}

void gameLoop()
{
	boardFab *BF = new boardFab();
	pawnFab *PF = new pawnFab();
	gameHandler *handler = new gameHandler(BF, PF);

	while (1)
	{
		std::cout << handler->getBoard()->getString();

		int pawnIndex = inputresult("select pawn (9 quits game):");
		if(pawnIndex == 9)
			break;

		iPawn *chsnPawn = handler->getMoveAblePawns()[pawnIndex];
		std::cout << handler->getBoard()->getString(chsnPawn);
		std::vector<std::pair<int,int>> moves = handler->getBoard()->getMoves(chsnPawn);
		unsigned int mvIndex = inputresult("select move:");

		if (mvIndex >  moves.size())
		{
			std::cout << "move was invalid. please try again:";
			continue;
		}

		gameState state = handler->makeTurn(chsnPawn, std::get<0>(moves[mvIndex]), std::get<1>(moves[mvIndex]));

		if (state == INVALID_MOVE)
			std::cout << "move was invalid. please try again:";

		if (state == BLACK_WON || state == WHITE_WON)
		{
			std::cout << "congratulations on winning!";
			break;
		}
	}
	delete handler;
	delete BF;
	delete PF;
}

void printHowTo()
{
	std::cout << "\n\nHow to play\n";
	std::cout << "===============\n";
	std::cout << "The goal of the game is getting the orb (O)\n";
	std::cout << "to the other side of the field.\n";
	std::cout << "\nThe pawns that do not have an orb can move, while\n";
	std::cout << "the pawns with the orb can only transfer it to another pawn.\n";
	std::cout << "The orb can be transfered horizontally, vertically\n";
	std::cout << "and diagonally. The first player to transfer it to\n";
	std::cout << "the enemy's side get's a cookie! (you're buying.)\n";
	std::cout << "-----------------------\n";
}

void printMenu()
{
	std::cout << "\n\nChess puzzle\n";
	std::cout << "===============\n";
	std::cout << "(1) play\n";
	std::cout << "(2) how to play\n";
	std::cout << "-----------------------\n";
	std::cout << "(9) QUIT\n\n";
	std::cout << "choice : ";
}

int main()
{
	bool quit = false;

	while (!quit)
	{
		char choice = '\0';
		printMenu();
		std::cin >> choice;
		std::cin.ignore();

		switch (choice)
		{
			case '1' :
			gameLoop();
			break;
			case '2' :
			printHowTo();
			break;
			case '9' :
			quit = true;
			break;
			default:
			std::cout << "\n\nPlease type in a correct input. (" << choice << ")" << std::endl;
			break;
		}
	}
}
