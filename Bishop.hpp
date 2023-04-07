#pragma once
#include "Piece.hpp"

namespace model {

	class Bishop : public Piece
	{
	public:
		Bishop(Team team) : Piece(team) {};
		std::list<Location> getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
	private:

	};

}

