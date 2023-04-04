#include "Queen.hpp"
std::list<Location> Queen::getPossiblePositions() const
{
	return std::list<Location>();
}

void Queen::display(std::ostream& out) const {
	out << "Q";
}

