#pragma once
#include "Piece.hpp"

namespace model {

	class King : public Piece {
	public:
		King(Team team);
		std::list<Location> getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
	private:
		static int instanceCount;
	};

}