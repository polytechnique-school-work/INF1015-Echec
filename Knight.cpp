#include "Knight.hpp"
std::list<Location> Knight::getPossiblePositions() const
{
	return std::list<Location>();
}

void Knight::display(std::ostream& out) const {
	out << "C";
}

