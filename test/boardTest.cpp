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
		std::vector<mPawn*> Pawns;

		boardTest()
		{
			for (int i = 0; i < 5; i++)
			{
				mPawn *T = new mPawn;
				Pawns.push_back(T);
			}

			std::vector<pawn*> input(Pawns.begin(), Pawns.end());
			B = new board(input);
		}

		~boardTest()
		{
			delete B;
			B = NULL;
			for (auto item: Pawns)
			{
				delete item;
				item = NULL;
			}
		}
};

TEST_F(boardTest, movePawnNormal)
{
    for (auto item: Pawns)
	{
		EXPECT_CALL(*item, getXPos()).WillRepeatedly(Return(0));
		EXPECT_CALL(*item, getYPos()).WillRepeatedly(Return(0));
	}

	EXPECT_CALL(P, setPosition(2, 3)).WillOnce(Return(true));

	EXPECT_EQ(B->movePawn(&P, 2, 3), true);
}

TEST_F(boardTest, movePawnOnPawn)
{
    for (auto item: Pawns)
	{
		EXPECT_CALL(*item, getXPos()).WillRepeatedly(Return(0));
		EXPECT_CALL(*item, getYPos()).WillRepeatedly(Return(0));
	}

	EXPECT_EQ(B->movePawn(&P, 0, 0), false);
}

TEST_F(boardTest, transferOrbNormal)
{
	EXPECT_CALL(*Pawns[0], getXPos()).WillRepeatedly(Return(0));
	EXPECT_CALL(*Pawns[0], getYPos()).WillRepeatedly(Return(0));

	EXPECT_CALL(*Pawns[1], getXPos()).WillRepeatedly(Return(3));
	EXPECT_CALL(*Pawns[1], getYPos()).WillRepeatedly(Return(3));
	
	EXPECT_EQ(B->transferOrb(Pawns[0], Pawns[1]), true);
}
