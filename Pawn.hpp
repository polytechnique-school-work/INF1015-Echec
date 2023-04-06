#pragma once
#include "Piece.hpp"

namespace model {

	class Pawn : public Piece {
	public:
		Pawn(Team team) : Piece(team) {};
		std::list<Location> getPossiblePositions(BoardContainer* board, Location& loc) const;
		void display(std::ostream& out) const;
	};

}