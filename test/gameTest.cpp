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
		std::vector<pawn*> tstWhite;
		std::vector<pawn*> tstBlack;
		mBoardFab *BF = new mBoardFab();
		mPawnFab *PF = new mPawnFab();

		gameTest()
		{
			EXPECT_CALL(*PF, createPawn(_, _)).WillRepeatedly(Return(new mPawn(0,0)));
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
			G = NULL;
			BF = NULL;
			PF = NULL;
		}
};

TEST(gameTest, plcholder)
{
	// placeholder for refactor so constructor gets executed
	EXPECT_EQ(true, true);
}
