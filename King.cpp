#include "King.hpp"
#include "Board.hpp"

using namespace model;
King::King(Team team) : Piece(team), bypass(false)
{
	if (instanceCount == 2) {
		throw std::logic_error("Impossible de créer plus de deux rois.");
	}
	instanceCount += 1;
}

model::King::~King()
{
	if (!this->bypass) instanceCount--;
}
LocationContainer King::getPossiblePositions([[maybe_unused]] Location& loc) const
{
	return { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
}

// Pas dans les lignes couvertes par les tests : permet d'afficher lors des tests
void King::display(std::ostream& out) const {
	out << "K";
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