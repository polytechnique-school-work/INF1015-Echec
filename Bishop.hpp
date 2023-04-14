#pragma once
#include "Piece.hpp"

namespace model {

	class Bishop : public Piece
	{
	public:
		Bishop(Team team) : Piece(team) {};
		LocationContainer getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
		std::string getName();
		std::string getTag();
	private:
	};

}

