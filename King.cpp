#include "King.hpp"
#include "Board.hpp"

using namespace model;
King::King(Team team) : Piece(team)
{
}

LocationContainer King::getPossiblePositions([[maybe_unused]] Location& loc) const
{
	return { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
}


// Pas dans les lignes couvertes par les tests : utile pour la vue
std::string model::King::getName()
{
	return "king";
}

std::string model::King::getTag()
{
	return "K";
}

int King::instanceCount = 0;