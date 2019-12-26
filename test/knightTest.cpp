#include "gtest/gtest.h"
#include "../src/knight.h"
#include <iostream>

//
// pawns should be moving in an L like shape. same as knights in chess.
//

struct pawnTest : testing::Test
{
	protected:
		knight *P;

		pawnTest()
		{
			P = new knight(0, 0);
		}

		~pawnTest()
		{
			delete P;
			P = NULL;
		}
};

TEST_F(pawnTest, getSetXPosition)
{
	ASSERT_EQ(0, P->getXPos());

	P->setPosition(1, 2);
	ASSERT_EQ(1, P->getXPos());
}

TEST_F(pawnTest, getSetYPosition)
{
	ASSERT_EQ(0, P->getYPos());

	P->setPosition(1, 2);
	ASSERT_EQ(2, P->getYPos());
}

TEST_F(pawnTest, toggleHasOrb)
{
	P->toggleOrb();
	ASSERT_EQ(true, P->hasOrb());
}

TEST_F(pawnTest, setNegativePosition)
{
	ASSERT_EQ(P->setPosition(-1, -5), false);
}

TEST_F(pawnTest, moveNoLShape)
{
	ASSERT_EQ(P->setPosition(1, 1), false);
}

TEST_F(pawnTest, moveLShape)
{
	ASSERT_EQ(P->setPosition(2, 1), true);
}

TEST_F(pawnTest, getPossibleMoves)
{
	int steps[][2] = {{-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}, {-2,1}};
	std::vector<std::pair<int,int>> result = P->getMoves(1);
	
	for (size_t i = 0; i < result.size(); i++)
	{
		EXPECT_EQ(std::get<0>(result[i]), steps[i][0]);
		EXPECT_EQ(std::get<1>(result[i]), steps[i][1]);
	}
}

TEST_F(pawnTest, getPossibleMovesOrb)
{
	int steps[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
	P->toggleOrb();
	std::vector<std::pair<int,int>> result = P->getMoves(1);

	for (size_t i = 0; i < result.size(); i++)
	{
		EXPECT_EQ(std::get<0>(result[i]), steps[i][0]);
		EXPECT_EQ(std::get<1>(result[i]), steps[i][1]);
	}
}