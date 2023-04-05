#include "Rock.hpp"
std::list<Location> Rock::getPossiblePositions() const
{
	std::list<Location> locations = {};

	for (int x = -7; x <= 7; ++x) {
		if (x == 0) continue;
		locations.push_back(Location(x, 0));
		locations.push_back(Location(0, x));
	}

	return locations;
}

void Rock::display(std::ostream& out) const {
	out << "R";
}
