#include "King.hpp"
std::list<Location> King::getPossiblePositions() const
{
	return std::list<Location>();
}
void King::display(std::ostream& out) const {
	out << "King" << std::endl;
}