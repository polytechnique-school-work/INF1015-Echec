#include "King.hpp"
#include "Board.hpp"

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
	return { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
}

void King::display(std::ostream& out) const {
	out << "K";
}

int King::instanceCount = 0;