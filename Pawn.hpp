#pragma once
#include "Piece.hpp"

class Pawn : public Piece {
public:
	/*friend iostream& operator<<(iostream& out, const Piece& piece) {
		out << "Pion" << endl;
		return out;
	}*/
	void getPossiblePositions() const {}

	void display(std::ostream& out) const;
	
};