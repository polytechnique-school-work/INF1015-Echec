#include "Queen.hpp"

using namespace model;
std::list<Location> Queen::getPossiblePositions(Location& loc) const
{
	std::list<Location> bishopPositions = Bishop(this->team).getPossiblePositions(loc);
	std::list<Location> rockPositions = Rock(this->team).getPossiblePositions(loc);

	bishopPositions.sort();
	rockPositions.sort();
	bishopPositions.merge(rockPositions);
	bishopPositions.unique();
	return bishopPositions;
}

void Queen::display(std::ostream& out) const {
	out << "Q";
}

std::string model::Queen::getName()
{
	return "queen";
}

