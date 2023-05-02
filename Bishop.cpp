#include "Bishop.hpp"
#include "Board.hpp";

namespace model {

	LocationContainer Bishop::getPossiblePositions(Location& loc) const
	{
		LocationContainer locations = {};
		for (int i = -1; i <= 1; i += 2) {
			for (int j = -1; j <= 1; j += 2) {
				for (int val = 1; val <= BOARD_SIZE; val++) {
					int relX = val * j;
					int relY = val * i;
					int x = relX + loc.first;
					int y = relY + loc.second;
					if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) continue;

					PieceContainer& pieceCtr = Board::getInstance().getBoardContainer()[x][y];
					// On ajoute la pièce seulement si et seulement si
					// La pièce n'est pas limitée par une pièce d'une même équipe
					// ET qu'elle n'a la possibilité que de manger une seule pièce.
					//cout << x << " " << y << endl;
					if (pieceCtr.has_value()) {
						Piece& piece = **pieceCtr;
						if (piece.getTeam() == this->team) {
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

	// Pas dans les lignes couvertes par les tests : permet d'afficher lors des tests
	void Bishop::display(std::ostream& out) const {
		out << "F";
	}

	// Pas dans les lignes couvertes par les tests : utile pour la vue
	std::string model::Bishop::getName()
	{
		return "bishop";
	}

	std::string model::Bishop::getTag()
	{
		return "F";
	}

}