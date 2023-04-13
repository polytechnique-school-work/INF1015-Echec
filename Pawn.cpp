#include "Pawn.hpp"
#include "Board.hpp"
using namespace model;
LocationContainer Pawn::getPossiblePositions(Location& loc) const
{
	// TODO : En passant : si le dernier pion a bougé de 2, il peut le manger (regarder l'historique).
	// Retirer la location si y'a une pièce devant.

	Board& board = Board::getInstance();
	int position = this->team == Team::WHITE ? -1 : 1;
	LocationContainer locations = {};


	/*
	*	Pion qui mange
	*/
	LocationContainer temp = { {1, position}, {-1, position} };
	for (Location& pos : temp) {

		Location boardLocation = { loc.first + pos.first, loc.second + pos.second };

		if (boardLocation.first < 0 || boardLocation.first >= BOARD_SIZE || boardLocation.second < 0 || boardLocation.second >= BOARD_SIZE) {
			continue;
		}

		PieceContainer& pieceCtr = board.getPiece(boardLocation);

		if (pieceCtr && pieceCtr.has_value()) {
			locations.push_back(pos);
		}
	}



	/*
	*	Avancement du pion
	*/
	LocationContainer secondList = { Location(0, 1 * position), Location(0, 2 * position) };
	for (Location& pos : secondList) {
		Location boardLocation = { loc.first + pos.first, loc.second + pos.second };
		if (boardLocation.first < 0 || boardLocation.first >= BOARD_SIZE || boardLocation.second < 0 || boardLocation.second >= BOARD_SIZE) {
			continue;
		}
		else if (board.getPiece({ boardLocation.first, boardLocation.second }).has_value()) {
			continue;
		}

		if (pos == Location(0, 2 * position) && this->getMoves()) {
			continue;
		}
		locations.push_back(pos);
	}

	return locations;
}
void Pawn::display(std::ostream& out) const {
	out << "P";
}

std::string model::Pawn::getName()
{
	return "pawn";
}
