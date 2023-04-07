#pragma once
#include "Piece.hpp"

namespace model {

	class Pawn : public Piece {
	public:
		Pawn(Team team) : Piece(team) {};
		std::list<Location> getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
	};

}