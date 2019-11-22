#include "gtest/gtest.h"
#include "../src/gameHandler.h"
#include "../src/gameState.h"
#include "../src/pawn.h"
#include "mockBoardFab.h"
#include "mockPawnFab.h"
#include "mockBoard.h"
#include "mockPawn.h"
#include <iostream>

using ::testing::SaveArg;
using ::testing::Return;
using ::testing::_;

struct gameTest : testing::Test
{
	protected:
		gameHandler *G;
		mBoardFab *BF = new mBoardFab();
		mPawnFab *PF = new mPawnFab();

		gameTest()
		{
			G = new gameHandler(BF, PF);
		}

		~gameTest()
		{
			delete G;
			delete BF;
			delete PF;
			G = NULL;
			BF = NULL;
			PF = NULL;
		}
};

TEST(constructTest, FabsCalled)
{
	std::vector<pawn*> tmpWhite;
	std::vector<pawn*> tmpBlack;
	mPawnFab *PF  = new mPawnFab();
	mBoardFab *BF = new mBoardFab();
	pawn *tstPawn = new mPawn(0,0);
	board *result = new mBoard(tmpWhite, tmpBlack);

	EXPECT_CALL(*PF, createPawn(_, _)).WillRepeatedly(Return(tstPawn));
	EXPECT_CALL(*BF, create5x5(_, _)).WillOnce(DoAll(SaveArg<0>(&tmpWhite), 
									  SaveArg<1>(&tmpBlack), Return(result)));

	gameHandler *G = new gameHandler(BF, PF);

	for (auto item : tmpWhite)
		delete item;

	for (auto item : tmpBlack)
		delete item;

	delete G;
	delete BF;
	delete PF;
	delete tstPawn;
}