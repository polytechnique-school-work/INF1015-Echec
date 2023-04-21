#pragma once
#include "Piece.hpp"

namespace model {

	class King : public Piece {
	public:
		King(Team team);
		~King();
		LocationContainer getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
		std::string getName();
		std::string getTag();
	private:
		bool bypass;
		static int instanceCount;
	};

}