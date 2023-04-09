#pragma once
#include "Piece.hpp"

namespace model {

	class Knight : public Piece
	{
	public:
		Knight(Team team) : Piece(team) {};
		std::list<Location> getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
		std::string& getName();
	private:
		std::string name = "knight";
	};

}

