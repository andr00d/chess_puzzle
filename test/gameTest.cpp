#include "gtest/gtest.h"
#include "../src/gameHandler.h"
#include "../src/gameState.h"
#include "../src/iPawn.h"
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
		std::vector<iPawn*> tstWhite;
		std::vector<iPawn*> tstBlack;
		mBoardFab *BF = new mBoardFab();
		mPawnFab *PF = new mPawnFab();
		mPawn *tstPawn = new mPawn(0,0);

		gameTest()
		{
			EXPECT_CALL(*PF, createPawn(_, _)).WillRepeatedly(Return(tstPawn));
			EXPECT_CALL(*BF, create5x5(_, _)).WillOnce(DoAll(SaveArg<0>(&tstWhite), 
											SaveArg<1>(&tstBlack), 
											Return(new mBoard(tstWhite, tstBlack))));

			G = new gameHandler(BF, PF);
		}

		~gameTest()
		{
			delete G;
			delete BF;
			delete PF;
			delete tstPawn;
			G = NULL;
			BF = NULL;
			PF = NULL;

			for (auto item : tstWhite)
				delete item;
			
			for (auto item : tstBlack)
				delete item;
		}
};

TEST_F(gameTest, moveablePawns)
{
	//placeholder for refactor so everything gets called
	std::vector<iPawn*> result = G->getMoveAblePawns();
	EXPECT_EQ(true, true);
}
