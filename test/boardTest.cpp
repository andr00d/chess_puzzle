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
				EXPECT_CALL(*white, setPosition(i+1, 0)).WillOnce(Return(true));
				EXPECT_CALL(*black, setPosition(i+1, 6)).WillOnce(Return(true));
				BlackPawns.push_back(black);
				WhitePawns.push_back(white);
			}

			EXPECT_CALL(*WhitePawns[2], toggleOrb());
			EXPECT_CALL(*BlackPawns[2], toggleOrb());

			std::vector<iPawn*> WInput(WhitePawns.begin(), WhitePawns.end());
			std::vector<iPawn*> BInput(BlackPawns.begin(), BlackPawns.end());
			B = new board(WInput, BInput);
		}

		~boardTest()
		{
			delete B;
			B = NULL;
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

TEST(constructTest, emptyVector)
{
	std::vector<iPawn*> WhitePawns;
	std::vector<iPawn*> BlackPawns;
	ASSERT_ANY_THROW(new board(WhitePawns, BlackPawns));
}

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

	std::vector<std::pair<int, int>> result = B->getMoves(WhitePawns[0]);

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

TEST_F(boardTest, checkPrint)
{
	for (size_t i = 0; i < 5; i++)
	{
		EXPECT_CALL(*WhitePawns[i], getXPos()).WillRepeatedly(Return(i+1));
		EXPECT_CALL(*WhitePawns[i], getYPos()).WillRepeatedly(Return(0));
		EXPECT_CALL(*WhitePawns[i], hasOrb()).WillRepeatedly(Return(false));
		EXPECT_CALL(*BlackPawns[i], getXPos()).WillRepeatedly(Return(i+1));
		EXPECT_CALL(*BlackPawns[i], getYPos()).WillRepeatedly(Return(6));
		EXPECT_CALL(*BlackPawns[i], hasOrb()).WillRepeatedly(Return(false));
	}
	
	EXPECT_CALL(*WhitePawns[2], hasOrb()).WillRepeatedly(Return(true));
	EXPECT_CALL(*BlackPawns[2], hasOrb()).WillRepeatedly(Return(true));

	std::string expectedString = R"(
+---+---+---+---+---+---+---+
|   | X | X | O | X | X |   |
+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+
|   | X | X | O | X | X |   |
+---+---+---+---+---+---+---+
)";

	EXPECT_EQ(B->getString(), expectedString);
}

TEST_F(boardTest, checkWinWhite)
{
	setExpectPos(0, 0);
	EXPECT_CALL(*WhitePawns[2], hasOrb()).WillOnce(Return(true));
	EXPECT_CALL(*WhitePawns[2], getYPos()).WillOnce(Return(6));

	EXPECT_EQ(B->checkWin(), true);
}

TEST_F(boardTest, checkWinBlack)
{
	setExpectPos(0, 1);
	EXPECT_CALL(*BlackPawns[2], hasOrb()).WillOnce(Return(true));
	EXPECT_CALL(*BlackPawns[2], getYPos()).WillOnce(Return(0));

	EXPECT_EQ(B->checkWin(), true);
}