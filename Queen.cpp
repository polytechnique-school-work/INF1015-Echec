#include "Queen.hpp"
std::list<Location> Queen::getPossiblePositions() const
{
	std::list<Location> bishopPositions = Bishop(this->team).getPossiblePositions();
	std::list<Location> rockPositions = Rock(this->team).getPossiblePositions();

	bishopPositions.merge(rockPositions);
	bishopPositions.unique();

	return bishopPositions;
}

void Queen::display(std::ostream& out) const {
	out << "Q";
}

