#pragma once
#include "Piece.hpp"

namespace model {

	class Pawn : public Piece {
	public:
		Pawn(Team team) : Piece(team) {};
		LocationContainer getPossiblePositions(Location& loc) const;
		std::string getName();
		std::string getTag();
		void removeEatPosition(Location& loc, LocationContainer& locations) const;
		void removeForwardDirection(Location& loc, LocationContainer& locations) const;
	private:
	};

}