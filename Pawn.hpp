#pragma once
#include "Piece.hpp"

namespace model {

	class Pawn : public Piece {
	public:
		Pawn(Team team) : Piece(team) {};
		LocationContainer getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
		std::string getName();
		std::string getTag();
	private:
	};

}