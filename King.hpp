#pragma once
#include "Piece.hpp"

class King: public Piece {
public:
	void getPossiblePositions() const {}
	void display(std::ostream& out) const;
private:

};