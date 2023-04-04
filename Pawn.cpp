#include "Pawn.hpp"
std::list<Location> Pawn::getPossiblePositions() const
{
	int position = this->team == Team::WHITE ? -1 : 1;
	std::list<Location> locations = {};
	locations.push_back(Location(0, 1 * position));
	locations.push_back(Location(0, 2 * position));
	return locations;
}
void Pawn::display(std::ostream& out) const {
	out << "P";
}