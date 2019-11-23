#include "gtest/gtest.h"
#include "../src/gameHandler.h"
#include "../src/gameState.h"
#include "../src/iPawn.h"
#include "mockBoardFab.h"
#include "mockPawnFab.h"
#include "mockBoard.h"
#include "mockPawn.h"
#include <iostream>

using ::testing::SaveArg;
using ::testing::Return;
using ::testing::_;

struct gameTest : testing::Test
{
	protected:
		gameHandler *G;
		std::vector<iPawn*> tstWhite;
		std::vector<iPawn*> tstBlack;
		mBoard *tstBoard = new mBoard(tstWhite, tstBlack);
		mBoardFab *BF = new mBoardFab();
		mPawnFab *PF = new mPawnFab();
		mPawn *tstPawn = new mPawn(0,0);

		gameTest()
		{
			EXPECT_CALL(*PF, createPawn(_, _)).WillRepeatedly(Return(tstPawn));
			EXPECT_CALL(*BF, create5x5(_, _)).WillOnce(DoAll(SaveArg<0>(&tstWhite), 
											SaveArg<1>(&tstBlack), 
											Return(tstBoard)));

			G = new gameHandler(BF, PF);
		}

		~gameTest()
		{
			delete G;
			delete BF;
			delete PF;
			delete tstPawn;
			G = NULL;
			BF = NULL;
			PF = NULL;

			for (auto item : tstWhite)
				delete item;
			
			for (auto item : tstBlack)
				delete item;
		}
};

TEST_F(gameTest, moveablePawnsBegin)
{
	std::vector<std::pair<int,int>> tstresult;
	tstresult.push_back(std::pair<int,int>(1,2));

	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, getMoves(_)).WillRepeatedly(Return(tstresult));

	std::vector<iPawn*> result = G->getMoveAblePawns();
	EXPECT_EQ(result.size(), 5);
}


TEST_F(gameTest, makeTurnNormal)
{
	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, movePawn(_, _, _)).WillOnce(Return(true));
	EXPECT_EQ(G->makeTurn(tstWhite[0], 0, 2), VALID_MOVE);
}

TEST_F(gameTest, makeTurnInvalid)
{
	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, movePawn(_, _, _)).WillOnce(Return(false));
	EXPECT_EQ(G->makeTurn(tstWhite[0], 0, 0), INVALID_MOVE);
}

TEST_F(gameTest, makeTwoTurnsSameColor)
{
	EXPECT_CALL(*tstBoard, movePawn(tstWhite[0], _, _)).WillOnce(Return(true));
	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));

	EXPECT_EQ(G->makeTurn(tstWhite[0], 0, 2), VALID_MOVE);
	EXPECT_EQ(G->makeTurn(tstWhite[1], 1, 2), INVALID_MOVE);
}