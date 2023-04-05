#pragma once
#include "Piece.hpp"
#include "Bishop.hpp"
#include "Rock.hpp"
class Queen : public Piece
{
public:
	Queen(Team team) : Piece(team) {};
	std::list<Location> getPossiblePositions(Board& board) const;
	void display(std::ostream& out) const;
private:

};

