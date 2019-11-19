#include "gtest/gtest.h"
#include "../src/pawn.h"
#include <iostream>

//
// pawns should be moving in an L like shape. same as knights in chess.
//

struct pawnTest : testing::Test
{
	protected:
		pawn *P;

		pawnTest()
		{
			P = new pawn();
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

	P->setPosition(5, 6);
	ASSERT_EQ(5, P->getXPos());
}

TEST_F(pawnTest, getSetYPosition)
{
	ASSERT_EQ(0, P->getYPos());

	P->setPosition(5, 6);
	ASSERT_EQ(6, P->getYPos());
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
	ASSERT_EQ(P->setPosition(3, 6), false);
	ASSERT_EQ(P->setPosition(5, 6), false);
}

TEST_F(pawnTest, moveLShape)
{
	P->setPosition(3, 3);
	ASSERT_EQ(P->setPosition(2, 1), true);
	ASSERT_EQ(P->setPosition(4, 1), true);
	ASSERT_EQ(P->setPosition(2, 4), true);
}

