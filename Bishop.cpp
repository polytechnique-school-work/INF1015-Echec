#include "Bishop.hpp"
std::list<Location> Bishop::getPossiblePositions(Board& board) const
{
	std::list<Location> locations = {};

	for (int i = -1; i <= 1; i += 2) {
		for (int j = -1; j <= 1; j += 2) {
			for (int k = 1; k < 8; ++k) {
				int row = i * k;
				int column = j * k;
				if (row >= 0 && row < 8 && column >= 0 && column < 8) {
					locations.push_back(Location(row, column));
				}
			}
		}
	}

	return locations;
}

void Bishop::display(std::ostream& out) const {
	out << "F";
}

