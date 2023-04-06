#pragma once
#include "Board.hpp"

namespace {

	class Game {
	public:
		void nextTurn();
	private:
		Team turn = Team::WHITE;
		std::optional<Team> winner;
	};

}