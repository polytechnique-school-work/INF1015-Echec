#include "Pawn.hpp"
#include "Board.hpp"
using namespace model;
LocationContainer Pawn::getPossiblePositions(Location& loc) const
{
	Board& board = Board::getInstance();
	int position = this->team == Team::WHITE ? -1 : 1;
	LocationContainer locations = { {1, position}, {-1, position} };

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
			break;
		}

		if (pos == Location(0, 2 * position) && this->getMoves()) {
			continue;
		}

		locations.push_back(pos);
	}

	return locations;
}

// Pas dans les lignes couvertes par les tests : permet d'afficher lors des tests
void Pawn::display(std::ostream& out) const {
	out << "P";
}

// Pas dans les lignes couvertes par les tests : utile pour la vue
std::string model::Pawn::getName()
{
	return "pawn";
}

std::string model::Pawn::getTag()
{
	return "P";
}

void model::Pawn::removeForwardDirection(Location& loc, LocationContainer& locations) const {
	Board& board = Board::getInstance();
	int position = this->team == Team::WHITE ? -1 : 1;
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

		locations.remove(pos);
	}
}

void model::Pawn::removeEatPosition(Location& loc, LocationContainer& locations) const
{
	Board& board = Board::getInstance();
	int position = this->team == Team::WHITE ? -1 : 1;
	LocationContainer temp = { {1, position}, {-1, position} };
	for (Location& pos : temp) {

		Location boardLocation = { loc.first + pos.first, loc.second + pos.second };

		if (boardLocation.first < 0 || boardLocation.first >= BOARD_SIZE || boardLocation.second < 0 || boardLocation.second >= BOARD_SIZE) {
			continue;
		}

		PieceContainer& pieceCtr = board.getPiece(boardLocation);

		if (!(pieceCtr && pieceCtr.has_value())) {
			locations.remove(pos);
		}
	}
}
