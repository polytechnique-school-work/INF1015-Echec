#pragma once
#include "Piece.hpp"

class King: public Piece {
public:
	King(Team team) : Piece(team) {};
	std::list<Location> getPossiblePositions(Board& board) const;
	void display(std::ostream& out) const;
private:

};