#pragma once
#include "Piece.hpp"

class Pawn : public Piece {
public:
	Pawn(Team team) : Piece(team) {};
	std::list<Location> getPossiblePositions() const;
	void display(std::ostream& out) const;
};