#include "gtest/gtest.h"
#include "../src/pawn.h"
#include <iostream>



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

TEST_F(pawnTest, setNegativePosition)
{
	EXPECT_ANY_THROW(P->setPosition(-1, -5));
}

TEST_F(pawnTest, toggleHasOrb)
{
	P->toggleOrb();
	ASSERT_EQ(true, P->hasOrb());
}
