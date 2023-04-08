#include "King.hpp"

using namespace model;
King::King(Team team) : Piece(team)
{
	if (instanceCount == 2) {
		throw std::logic_error("Impossible de créer plus de deux rois.");
	}
	instanceCount += 1;
}
King::King(Team team, bool bypass): Piece(team)
{

}
std::list<Location> King::getPossiblePositions(Location& loc) const
{
	// Les positions ont ete reprises de mon ancien jeu d'echec en python : https://github.com/Sportek/chess
	return { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
}

void King::display(std::ostream& out) const {
	out << "K";
}

int King::instanceCount = 0;