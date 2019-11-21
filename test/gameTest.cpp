#include "gtest/gtest.h"
#include "../src/gameHandler.h"
#include "../src/gameState.h"
#include "mockBoardFab.h"
#include "mockPawnFab.h"
#include "mockBoard.h"
#include <iostream>


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

TEST_F(gameTest, functions_good)
{
	EXPECT_EQ(true, true);
}