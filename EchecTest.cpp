﻿
#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

#include "Board.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Queen.hpp"
#include "Pawn.hpp"
#include "Rock.hpp"
#include "Bishop.hpp"
#include "Game.hpp"

using namespace model;

namespace test {

	TEST(Positions, calculate_king_safe) {
		const std::string board = "XXXXXXXXXXBFXXXXXXBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWKWPXXXXXXXXXXXXXXXXXXXXXXBCXXXXXXXXXXXXXXXXXXXXXXBRXXXXXXXXXXXXXXXXXXXXXX";

		Board& boardInstance = Board::getInstance();

		boardInstance.generateBoard(board);

		LocationContainer supposedPositions = { {4, 2}, {3, 4} };
		LocationContainer calculatedPositions = boardInstance.possibleMoves({ 3,3 });

		EXPECT_EQ(supposedPositions, calculatedPositions);
	}


	TEST(Positions, calculate_bishop) {
		const std::string board = "XXXXXXXXXXXXXXXXXXXXXXXXWPXXXXXXXXXXXXXXXXWFXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAA";

		Board& boardInstance = Board::getInstance();

		boardInstance.generateBoard(board);

		LocationContainer supposedPositions = { {6, 1}, {7, 0}, {4, 3}, {3, 4}, {2, 5}, {1, 6}, {0, 7}, {6, 3}, {7, 4} };
		LocationContainer calculatedPositions = boardInstance.possibleMoves({ 5, 2 });

		EXPECT_EQ(supposedPositions, calculatedPositions);
	}

	TEST(Positions, move_queen_possible) {

		const std::string board = "BRBCBFBQBKBFBCBRBPBPBPXXBPXXBPBPXXXXXXXXXXXXXXXXXXXXXXBPXXBPXXXXXXXXXXWPXXXXWPXXXXXXXXXXXXXXXXXXWPWPWPXXWPWPXXWPWRWCWFWQWKWFWCWR";

		Board& boardInstance = Board::getInstance();

		boardInstance.generateBoard(board);

		bool value = boardInstance.isMovePossible({ 3, 7 }, { 3, 5 });

		EXPECT_TRUE(value);
	}

	TEST(Positions, move_queen_board) {

		const std::string board = "BRBCBFBQBKBFBCBRBPBPBPXXBPXXBPBPXXXXXXXXXXXXXXXXXXXXXXBPXXBPXXXXXXXXXXWPXXXXWPXXXXXXXXXXXXXXXXXXWPWPWPXXWPWPXXWPWRWCWFWQWKWFWCWR";

		Board& boardInstance = Board::getInstance();

		boardInstance.generateBoard(board);


		boardInstance.movePiece({ 3, 7 }, { 3, 5 });

		std::string value = boardInstance.saveBoard();

		EXPECT_EQ(value, "BRBCBFBQBKBFBCBRBPBPBPXXBPXXBPBPXXXXXXXXXXXXXXXXXXXXXXBPXXBPXXXXXXXXXXWPXXXXWPXXXXXXXXWQXXXXXXXXWPWPWPXXWPWPXXWPWRWCWFXXWKWFWCWR");
	}


	TEST(Names, pieces_names_check) {
		// Permet de clear le board pour pouvoir créer des rois.
		const std::string board = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
		Board& boardInstance = Board::getInstance();
		boardInstance.generateBoard(board);

		std::vector<Piece*> pieces = { new King(Team::WHITE), new Queen(Team::BLACK), new Bishop(Team::BLACK), new Pawn(Team::WHITE), new Rock(Team::BLACK), new Knight(Team::BLACK) };

		std::string value = "";

		for (Piece* piece : pieces) {
			value += piece->getName();
			delete piece;
		}

		EXPECT_EQ(value, "kingqueenbishoppawnrockknight");
	}

	TEST(Game_end, check_if_mat) {

		const std::string board = "XXXXXXBKXXBRXXXXBPXXXXXXXXXXBPXXXXXXXXXXXXXXXXBPXXBPXXXXWRXXXXXXXXXXXXXXXXXXWPWPWPWPXXXXXXXXXXXXXXXXXXBPXXXXXXXXXXXXWRXXWKXXXXXX";
		Board& boardInstance = Board::getInstance();
		boardInstance.generateBoard(board);

		bool value = boardInstance.isMat(Team::WHITE);

		EXPECT_FALSE(value);
	}

	TEST(Game, check_if_switch_team) {
		model::Game::getInstance().setTurn(Team::WHITE);
		model::Team team = model::Game::getInstance().getTurn();
		EXPECT_EQ(team, Team::WHITE);
	}
}
#endif