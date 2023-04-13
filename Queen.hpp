#pragma once
#include "Piece.hpp"
#include "Bishop.hpp"
#include "Rock.hpp"

namespace model {
	class Queen : public Piece
	{
	public:
		Queen(Team team) : Piece(team) {};
		LocationContainer getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
		std::string getName();
	private:
	};
}

