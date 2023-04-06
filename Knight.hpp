#pragma once
#include "Piece.hpp"
class Knight : public Piece
{
public:
	Knight(Team team) : Piece(team) {};
	std::list<Location> getPossiblePositions(BoardContainer* board, Location& loc) const;
	void display(std::ostream& out) const;
private:

};

