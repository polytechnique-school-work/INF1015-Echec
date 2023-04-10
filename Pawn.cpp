#include "Pawn.hpp"
#include "Board.hpp"
using namespace model;
std::list<Location> Pawn::getPossiblePositions(Location& loc) const
{
	// TODO : En passant : si le dernier pion a bougé de 2, il peut le manger (regarder l'historique).
	Board& board = Board::getInstance();
	int position = this->team == Team::WHITE ? -1 : 1;
	std::list<Location> locations = {};

	std::list<Location> temp = { {1, position}, {-1, position} };
	for (Location& pos : temp) {
		Location boardLocation = { loc.first + pos.first, loc.second + pos.second };
		if (board.getPiece(boardLocation).has_value()) {
			locations.push_back(pos);
		}
	}

	locations.push_back(Location(0, 1 * position));
	if(!this->getMoves()) locations.push_back(Location(0, 2 * position));
	return locations;
}
void Pawn::display(std::ostream& out) const {
	out << "P";
}

std::string model::Pawn::getName()
{
	return "pawn";
}
