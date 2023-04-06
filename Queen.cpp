#include "Queen.hpp"

using namespace model;
std::list<Location> Queen::getPossiblePositions(BoardContainer* board, Location& loc) const
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

