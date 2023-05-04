#pragma once
#include "Piece.hpp"

namespace model {

	class King : public Piece {
	public:
		King(Team team);
		LocationContainer getPossiblePositions(Location& loc) const;
		std::string getName();
		std::string getTag();
	private:
		static int instanceCount;
	};

}