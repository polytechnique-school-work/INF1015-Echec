#include "King.hpp"
std::list<Location> King::getPossiblePositions() const
{
	// Les positions ont été reprises de mon ancien jeu d'échec en python : https://github.com/Sportek/chess
	return { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
}

void King::display(std::ostream& out) const {
	out << "K";
}