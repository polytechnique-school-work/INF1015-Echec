#pragma once
#include "Piece.hpp"
class Rock : public Piece
{
public:
	Rock(Team team) : Piece(team) {};
	std::list<Location> getPossiblePositions() const;
	void display(std::ostream& out) const;
private:

};

