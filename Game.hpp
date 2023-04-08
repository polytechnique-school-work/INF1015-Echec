#pragma once
#include "Board.hpp"

namespace model {

	class Game {
	public:
		void nextTurn();
	private:
		Team turn = Team::WHITE;
		std::optional<Team> winner;
	};
}