#include "Rock.hpp"
std::list<Location> Rock::getPossiblePositions(BoardContainer* board, Location& loc) const
{
	std::list<Location> locations = {};
	for (int i = -1; i <= 1; i += 2) {
		for (int j = -1; j <= 1; j += 2) {
			for (int val = 1; val <= 8; val++) {

				cout << i << endl;
				cout << j << endl;
				cout << val << endl;

				int relX = val * j;
				int relY = val * i;
				int x = relX + loc.first;
				int y = relY + loc.second;
				if (x < 0 || x > 8 || y < 0 || y > 8) continue;

				PieceContainer& pieceCtr = (*board)[x][y];
				// On ajoute la pièce seulement si et seulement si
				// La pièce n'est pas limitée par une pièce d'une même équipe
				// ET qu'elle n'a la possibilité que de manger une seule pièce.
				//cout << x << " " << y << endl;
				if (pieceCtr.has_value()) {
					Piece& piece = **pieceCtr;
					if (piece.getTeam() == this->team) {
						cout << "same team" << endl;
						break;
					}
					locations.push_back({ relX, relY });
					break;
				}
				locations.push_back({ relX, relY });
			}
		}
	}
	return locations;
}

void Rock::display(std::ostream& out) const {
	out << "R";
}
