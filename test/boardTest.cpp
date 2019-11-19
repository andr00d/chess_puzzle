#include "gtest/gtest.h"
#include "../src/board.h"
#include "mockPawn.h"
#include <iostream>


using ::testing::Return;
using ::testing::_;

struct boardTest : testing::Test
{
	protected:
		board *B;
		mPawn P;
		std::vector<pawn> pawns;

		boardTest()
		{
			for (int i = 0; i < 5; i++)
			{
				mPawn T;
				pawns.emplace_back(T);
			}
			
			B = new board(pawns);
		}

		~boardTest()
		{
			delete B;
		}
};

TEST_F(boardTest, movePawnNormal)
{
	EXPECT_CALL(P, setPosition(2, 3)).WillOnce(Return(true));

	EXPECT_EQ(B->movePawn(&P, 2, 3), true);
}

TEST_F(boardTest, movePawnOnPawn)
{
	EXPECT_CALL(P, getXPos()).WillRepeatedly(Return(0));
	EXPECT_CALL(P, getYPos()).WillRepeatedly(Return(0));

	EXPECT_EQ(B->movePawn(&P, 0, 0), false);
}
