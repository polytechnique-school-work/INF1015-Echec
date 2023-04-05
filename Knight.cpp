#include "Knight.hpp"
std::list<Location> Knight::getPossiblePositions(Board& board, Location& loc) const
{
	// Les positions ont été reprises de mon ancien jeu d'échec en python : https://github.com/Sportek/chess
	return { {1, -2}, {2, -1},{2, 1},{1, 2},{-1, 2},{ -2, 1},{ -2, -1},{ -1, -2} };
}

void Knight::display(std::ostream& out) const {
	out << "C";
}

