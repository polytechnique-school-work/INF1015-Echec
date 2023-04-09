#include "Knight.hpp"

using namespace model;
std::list<Location> Knight::getPossiblePositions(Location& loc) const
{
	// Les positions ont �t� reprises de mon ancien jeu d'�chec en python : https://github.com/Sportek/chess
	return { {1, -2}, {2, -1},{2, 1},{1, 2},{-1, 2},{ -2, 1},{ -2, -1},{ -1, -2} };
}

void Knight::display(std::ostream& out) const {
	out << "C";
}

std::string& model::Knight::getName()
{
	return name;
}

