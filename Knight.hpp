#pragma once
#include "Piece.hpp"
class Knight : public Piece
{
public:
	Knight(Team team) : Piece(team) {};
	std::list<Location> getPossiblePositions() const;
	void display(std::ostream& out) const;
private:

};

