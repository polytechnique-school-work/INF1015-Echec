#include "King.hpp"

using namespace model;
std::list<Location> King::getPossiblePositions(Location& loc) const
{
	// Les positions ont ete reprises de mon ancien jeu d'echec en python : https://github.com/Sportek/chess
	return { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
}

void King::display(std::ostream& out) const {
	out << "K";
}