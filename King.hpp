#pragma once
#include "Piece.hpp"

namespace model {

	class King : public Piece {
	public:
		King(Team team);
		King(Team team, bool bypass); // Aiguillage pour permettre un bypass du compteur.
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