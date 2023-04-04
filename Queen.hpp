#pragma once
#include "Piece.hpp"
class Queen : public Piece
{
public:
	Queen(Team team) : Piece(team) {};
	std::list<Location> getPossiblePositions() const;
	void display(std::ostream& out) const;
private:

};

