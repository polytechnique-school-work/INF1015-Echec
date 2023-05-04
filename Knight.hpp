#pragma once
#include "Piece.hpp"

namespace model {

	class Knight : public Piece
	{
	public:
		Knight(Team team) : Piece(team) {};
		LocationContainer getPossiblePositions(Location& loc) const;
		std::string getName();
		std::string getTag();
	private:
	};

}

