#pragma once
#include "Piece.hpp"
class Bishop : public Piece
{
public:
	Bishop(Team team) : Piece(team) {};
	std::list<Location> getPossiblePositions(Board& board) const;
	void display(std::ostream& out) const;
private:

};

