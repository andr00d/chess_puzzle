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
		std::vector<mPawn*> WhitePawns;
		std::vector<mPawn*> BlackPawns;

		boardTest()
		{
			for (int i = 0; i < 5; i++)
			{
				mPawn *black = new mPawn(0, 0);
				mPawn *white = new mPawn(0, 0);
				BlackPawns.push_back(black);
				WhitePawns.push_back(white);
			}

			std::vector<pawn*> WInput(WhitePawns.begin(), WhitePawns.end());
			std::vector<pawn*> BInput(BlackPawns.begin(), BlackPawns.end());
			B = new board(WInput, BInput);
		}

		~boardTest()
		{
			delete B;
			B = NULL;
			for (size_t i = 0; i < BlackPawns.size(); i++)
			{
				delete WhitePawns[i];
				delete BlackPawns[i];
				WhitePawns[i] = NULL;
				BlackPawns[i] = NULL;
			}
		}

		void setExpectPos(int X, int Y)
		{
			for (auto item: WhitePawns)
			{
				EXPECT_CALL(*item, getXPos()).WillRepeatedly(Return(X));
				EXPECT_CALL(*item, getYPos()).WillRepeatedly(Return(Y));
			}

			for (auto item: BlackPawns)
			{
				EXPECT_CALL(*item, getXPos()).WillRepeatedly(Return(X));
				EXPECT_CALL(*item, getYPos()).WillRepeatedly(Return(Y));
			}
		}
};

TEST_F(boardTest, movePawnNormal)
{
	setExpectPos(0, 0);
	EXPECT_CALL(*WhitePawns[0], setPosition(2, 3)).WillOnce(Return(true));

	EXPECT_EQ(B->movePawn(WhitePawns[0], 2, 3), true);
}

TEST_F(boardTest, movePawnOnItself)
{
	setExpectPos(0, 0);
	EXPECT_EQ(B->movePawn(WhitePawns[0], 0, 0), false);
}

TEST_F(boardTest, movePawnOnPawn)
{
	setExpectPos(0, 0);

	EXPECT_EQ(B->movePawn(WhitePawns[0], 0, 0), false);
}

TEST_F(boardTest, transferOrbDiagonal)
{
	setExpectPos(0, 0);

	EXPECT_CALL(*WhitePawns[0], getXPos()).WillRepeatedly(Return(1));
	EXPECT_CALL(*WhitePawns[0], getYPos()).WillRepeatedly(Return(1));
	EXPECT_CALL(*WhitePawns[0], toggleOrb());

	EXPECT_CALL(*WhitePawns[1], getXPos()).WillRepeatedly(Return(3));
	EXPECT_CALL(*WhitePawns[1], getYPos()).WillRepeatedly(Return(3));
	EXPECT_CALL(*WhitePawns[1], toggleOrb());
	
	EXPECT_EQ(B->transferOrb(WhitePawns[0], WhitePawns[1]), true);
}

TEST_F(boardTest, transferOrbCrooked)
{
	setExpectPos(0, 0);

	EXPECT_CALL(*WhitePawns[0], getXPos()).WillRepeatedly(Return(1));
	EXPECT_CALL(*WhitePawns[0], getYPos()).WillRepeatedly(Return(2));

	EXPECT_CALL(*WhitePawns[1], getXPos()).WillRepeatedly(Return(6));
	EXPECT_CALL(*WhitePawns[1], getYPos()).WillRepeatedly(Return(3));
	
	EXPECT_EQ(B->transferOrb(WhitePawns[0], WhitePawns[1]), false);
}

TEST_F(boardTest, transferOrbHorizontal)
{
	setExpectPos(0, 0);

	EXPECT_CALL(*WhitePawns[0], getXPos()).WillRepeatedly(Return(1));
	EXPECT_CALL(*WhitePawns[0], getYPos()).WillRepeatedly(Return(0));
	EXPECT_CALL(*WhitePawns[0], toggleOrb());

	EXPECT_CALL(*WhitePawns[1], getXPos()).WillRepeatedly(Return(3));
	EXPECT_CALL(*WhitePawns[1], getYPos()).WillRepeatedly(Return(0));
	EXPECT_CALL(*WhitePawns[1], toggleOrb());
	
	EXPECT_EQ(B->transferOrb(WhitePawns[0], WhitePawns[1]), true);
}

TEST_F(boardTest, transferOrbThroughPlayerHorizontal)
{
	setExpectPos(6, 0);

	EXPECT_CALL(*WhitePawns[0], getXPos()).WillRepeatedly(Return(0));
	EXPECT_CALL(*WhitePawns[0], getYPos()).WillRepeatedly(Return(0));

	EXPECT_CALL(*WhitePawns[1], getXPos()).WillRepeatedly(Return(1));
	EXPECT_CALL(*WhitePawns[1], getYPos()).WillRepeatedly(Return(0));

	EXPECT_CALL(*WhitePawns[2], getXPos()).WillRepeatedly(Return(3));
	EXPECT_CALL(*WhitePawns[2], getYPos()).WillRepeatedly(Return(0));
	
	EXPECT_EQ(B->transferOrb(WhitePawns[0], WhitePawns[2]), false);
}

TEST_F(boardTest, GetPossibleMoves)
{
	setExpectPos(1, 0);

	EXPECT_CALL(*WhitePawns[0], getXPos()).WillRepeatedly(Return(2));
	EXPECT_CALL(*WhitePawns[0], getYPos()).WillRepeatedly(Return(2));

	EXPECT_CALL(*WhitePawns[1], getXPos()).WillRepeatedly(Return(3));
	EXPECT_CALL(*WhitePawns[1], getYPos()).WillRepeatedly(Return(4));

	std::vector<std::pair<int, int>> result = B->GetMoves(WhitePawns[0]);

	EXPECT_EQ(result.size(), 6);

	int expected[][2] = {{0,1}, {0,3}, {1,4}, {3,0}, {4,1}, {4,3}};

    for (auto const& pair: result)
	{
		bool result = false;
		for (size_t i = 0; i < 6; i++)
		{
			if(expected[i][0] == std::get<0>(pair) && expected[i][1] == std::get<1>(pair))
				result = true;
		}
		EXPECT_TRUE(result);
	}
}