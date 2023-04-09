#pragma once
#include "Piece.hpp"

namespace model {

	class King : public Piece {
	public:
		King(Team team);
		King(Team team, bool bypass); // Aiguillage pour permettre un bypass du compteur.
		~King();
		std::list<Location> getPossiblePositions(Location& loc) const;
		void display(std::ostream& out) const;
		std::string& getName();
	private:
		bool bypass;
		static int instanceCount;
		std::string name = "king";
	};

}