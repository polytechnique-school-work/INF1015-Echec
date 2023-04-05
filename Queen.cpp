#include "Queen.hpp"
std::list<Location> Queen::getPossiblePositions(Board& board) const
{
	std::list<Location> bishopPositions = Bishop(this->team).getPossiblePositions(board);
	std::list<Location> rockPositions = Rock(this->team).getPossiblePositions(board);

	bishopPositions.merge(rockPositions);
	bishopPositions.unique();

	return bishopPositions;
}

void Queen::display(std::ostream& out) const {
	out << "Q";
}

