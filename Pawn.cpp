#include "Pawn.hpp"
using namespace model;
std::list<Location> Pawn::getPossiblePositions(Location& loc) const
{
	// TODO : Le pion mange en diagonale, à changer!
	// À refaire pour éviter qu'il saute par dessus un pion.
	int position = this->team == Team::WHITE ? -1 : 1;
	std::list<Location> locations = {};
	locations.push_back(Location(0, 1 * position));
	if(!this->getMoves()) locations.push_back(Location(0, 2 * position));
	return locations;
}
void Pawn::display(std::ostream& out) const {
	out << "P";
}