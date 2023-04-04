#include "Rock.hpp"
std::list<Location> Rock::getPossiblePositions() const
{
	return std::list<Location>();
}

void Rock::display(std::ostream& out) const {
	out << "R";
}
