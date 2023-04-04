#include "Bishop.hpp"
std::list<Location> Bishop::getPossiblePositions() const
{
	return std::list<Location>();
}

void Bishop::display(std::ostream& out) const {
	out << "F";
}

