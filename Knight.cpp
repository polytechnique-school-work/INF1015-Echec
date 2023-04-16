#include "Knight.hpp"

using namespace model;
LocationContainer Knight::getPossiblePositions([[maybe_unused]] Location& loc) const
{
	// Les positions ont �t� reprises de mon ancien jeu d'�chec en python : https://github.com/Sportek/chess
	return { {1, -2}, {2, -1},{2, 1},{1, 2},{-1, 2},{ -2, 1},{ -2, -1},{ -1, -2} };
}

void Knight::display(std::ostream& out) const {
	out << "C";
}

std::string model::Knight::getName()
{
	return "knight";
}

std::string model::Knight::getTag()
{
	return "C";
}

