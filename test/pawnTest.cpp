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

TEST_F(pawnTest, getXPosition)
{
	ASSERT_EQ(0, P->getXPos());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

