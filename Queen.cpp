#include "Queen.hpp"

using namespace model;
LocationContainer Queen::getPossiblePositions(Location& loc) const
{
	LocationContainer bishopPositions = Bishop(this->team).getPossiblePositions(loc);
	LocationContainer rockPositions = Rock(this->team).getPossiblePositions(loc);

	bishopPositions.sort();
	rockPositions.sort();
	bishopPositions.merge(rockPositions);
	bishopPositions.unique();
	return bishopPositions;
}

// Pas dans les lignes couvertes par les tests : utile pour la vue
std::string model::Queen::getName()
{
	return "queen";
}

std::string model::Queen::getTag()
{
	return "Q";
}

