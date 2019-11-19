#include "gtest/gtest.h"
#include "../src/board.h"
#include "mockPawn.h"
#include <iostream>



struct boardTest : testing::Test
{
	protected:
		board *B;
		mPawn P;

		boardTest()
		{
			B = new board();
		}

		~boardTest()
		{
			delete B;
		}
};

TEST_F(boardTest, movePawnNormal)
{
	EXPECT_CALL(P, setPosition(2, 3));

	B->movePawn(&P, 2, 3);
}
