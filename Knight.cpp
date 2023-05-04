#include "Knight.hpp"

using namespace model;
LocationContainer Knight::getPossiblePositions([[maybe_unused]] Location& loc) const
{
	// Les positions ont été reprises de mon ancien jeu d'échec en python : https://github.com/Sportek/chess
	return { {1, -2}, {2, -1},{2, 1},{1, 2},{-1, 2},{ -2, 1},{ -2, -1},{ -1, -2} };
}


// Pas dans les lignes couvertes par les tests : utile pour la vue
std::string model::Knight::getName()
{
	return "knight";
}

std::string model::Knight::getTag()
{
	return "C";
}

