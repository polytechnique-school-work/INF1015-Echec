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
King::King(Team team, bool bypass) : Piece(team), bypass(bypass)
{

}
model::King::~King()
{
	if (!this->bypass) instanceCount--;
}
std::list<Location> King::getPossiblePositions(Location& loc) const
{
	return { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
}

void King::display(std::ostream& out) const {
	out << "K";
}

std::string model::King::getName()
{
	return "king";
}

int King::instanceCount = 0;