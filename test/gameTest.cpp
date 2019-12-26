#include "gtest/gtest.h"
#include "../src/gameHandler.h"
#include "../src/gameState.h"
#include "../src/iPawn.h"
#include "mockBoardFab.h"
#include "mockPawnFab.h"
#include "mockBoard.h"
#include "mockKnight.h"
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
		mBoard *tstBoard;
		mBoardFab *BF = new mBoardFab();
		mPawnFab *PF = new mPawnFab();
		mKnight *tstPawn = new mKnight(0,0);

		gameTest()
		{
			for (size_t i = 0; i < 5; i++)
			{
				tstWhite.push_back(new mKnight(i+1,0));
				tstBlack.push_back(new mKnight(i+1,6));
			}
			
			tstBoard = new mBoard(tstWhite, tstBlack);

			EXPECT_CALL(*PF, createPawn(_, _)).WillRepeatedly(Return(tstPawn));
			EXPECT_CALL(*BF, create7x7(_, _)).WillOnce(Return(tstBoard));

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

TEST_F(gameTest, moveablePawnsTwoTurns)
{
	std::vector<std::pair<int,int>> tstresult;
	tstresult.push_back(std::pair<int,int>(1,2));

	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, getBlackPawns()).WillRepeatedly(Return(tstBlack));
	EXPECT_CALL(*tstBoard, getMoves(_)).WillRepeatedly(Return(tstresult));
	EXPECT_CALL(*tstBoard, checkWin()).WillRepeatedly(Return(false));
	EXPECT_CALL(*tstBoard, movePawn(_, _, _)).WillOnce(Return(true));

	std::vector<iPawn*> result = G->getMoveAblePawns();
	EXPECT_EQ(tstWhite, result);
	G->makeTurn(tstWhite[0], 1, 2);
	result = G->getMoveAblePawns();
	EXPECT_EQ(tstBlack, result);
}


TEST_F(gameTest, makeTurnNormal)
{
	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, checkWin()).WillRepeatedly(Return(false));
	EXPECT_CALL(*tstBoard, movePawn(_, _, _)).WillOnce(Return(true));
	EXPECT_EQ(G->makeTurn(tstWhite[0], 0, 2), VALID_MOVE);
}

TEST_F(gameTest, makeTurnInvalid)
{
	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, movePawn(_, _, _)).WillOnce(Return(false));
	EXPECT_CALL(*tstBoard, checkWin()).WillRepeatedly(Return(false));
	EXPECT_EQ(G->makeTurn(tstWhite[0], 0, 0), INVALID_MOVE);
}

TEST_F(gameTest, makeTwoTurnsSameColor)
{
	EXPECT_CALL(*tstBoard, movePawn(tstWhite[0], _, _)).WillOnce(Return(true));
	EXPECT_CALL(*tstBoard, movePawn(tstBlack[0], _, _)).WillOnce(Return(true));
	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, checkWin()).WillRepeatedly(Return(false));


	EXPECT_EQ(G->makeTurn(tstWhite[0], 0, 2), VALID_MOVE);
	EXPECT_EQ(G->makeTurn(tstWhite[1], 1, 2), INVALID_MOVE);

	EXPECT_EQ(G->makeTurn(tstBlack[0], 0, 4), VALID_MOVE);
	EXPECT_EQ(G->makeTurn(tstBlack[1], 1, 4), INVALID_MOVE);
}

TEST_F(gameTest, checkWhiteWin)
{
	EXPECT_CALL(*tstBoard, movePawn(_ , _, _)).WillRepeatedly(Return(true));
	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, checkWin()).WillOnce(Return(true));

	//board checks valid moves and win, so we can just cheat with the setup here.
	EXPECT_EQ(G->makeTurn(tstWhite[0], 3, 6), WHITE_WON);
}

TEST_F(gameTest, checkBlackWin)
{
	EXPECT_CALL(*tstBoard, movePawn(_ , _, _)).WillRepeatedly(Return(true));
	EXPECT_CALL(*tstBoard, getWhitePawns()).WillRepeatedly(Return(tstWhite));
	EXPECT_CALL(*tstBoard, checkWin()).WillOnce(Return(false)).WillOnce(Return(true));

	//board checks valid moves and win, so we can just cheat with the setup here.
	EXPECT_EQ(G->makeTurn(tstWhite[0], 1, 2), VALID_MOVE);
	EXPECT_EQ(G->makeTurn(tstBlack[0], 0, 3), BLACK_WON);
}