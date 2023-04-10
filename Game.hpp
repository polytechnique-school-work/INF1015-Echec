#pragma once
#include "Board.hpp"

namespace model {

	class Game {
	public:
		void nextTurn();
		static Game& getInstance();
		Team& getTurn();
	private:
		static std::unique_ptr<Game> $instance;
		Team turn = Team::WHITE;
		std::optional<Team> winner;
	};
}