
#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

#include "Board.hpp"

using namespace model;

TEST(Positions, calculate_king_safe) {
	const std::string board = "XXXXXXXXXXBFXXXXXXBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWKWPXXXXXXXXXXXXXXXXXXXXXXBCXXXXXXXXXXXXXXXXXXXXXXBRXXXXXXXXXXXXXXXXXXXXXX";

	Board& boardInstance = Board::getInstance();

	boardInstance.generateBoard(board);

	LocationContainer supposedPositions = { {4, 2}, {3, 4} };
	LocationContainer calculatedPositions = boardInstance.possibleMoves({ 3,3 });

	EXPECT_EQ(supposedPositions, calculatedPositions);
}


TEST(Positions, calculate_bishop) {
	const std::string board = "XXXXXXXXXXXXXXXXXXXXXXXXWPXXXXXXXXXXXXXXXXWFXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	Board& boardInstance = Board::getInstance();

	boardInstance.generateBoard(board);
	LocationContainer supposedPositions = { {6, 1}, {7, 0}, {4, 3}, {3, 4}, {2, 5}, {1, 6}, {0, 7}, {6, 3}, {7, 4} };
	LocationContainer calculatedPositions = boardInstance.possibleMoves({5, 2});

	EXPECT_EQ(supposedPositions, calculatedPositions);
}

#endif