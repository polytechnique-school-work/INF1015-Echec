#include "Queen.hpp"
std::list<Location> Queen::getPossiblePositions(Board& board, Location& loc) const
{
	std::list<Location> bishopPositions = Bishop(this->team).getPossiblePositions(board, loc);
	std::list<Location> rockPositions = Rock(this->team).getPossiblePositions(board, loc);

	bishopPositions.merge(rockPositions);
	bishopPositions.unique();

	return bishopPositions;
}

void Queen::display(std::ostream& out) const {
	out << "Q";
}

