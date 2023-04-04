#pragma once
#include "Piece.hpp"

class King: public Piece {
public:
	std::list<Location> getPossiblePositions() const;
	void display(std::ostream& out) const;
private:

};