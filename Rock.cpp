#include "Rock.hpp"

using namespace model;
using namespace std;

list<Location> Rock::getPossiblePositions(BoardContainer* board, Location& loc) const
{
	std::list<Location> locations = {};


	for (int i = -1; i < 1; i += 2)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 1; k <= 8; k++) {
				pair<int, int> possibilities[] = { {0, k}, {k, 0} };
				int relX = possibilities[j].first;
				int relY = possibilities[j].second;
				int x = relX + loc.first;
				int y = relY + loc.second;
				if (x < 0 || x > 7 || y < 0 || y > 7) continue;
				cout << x << " " << y << endl;

				PieceContainer& pieceCtr = (*board)[x][y];
				// On ajoute la pi�ce seulement si et seulement si
				// La pi�ce n'est pas limit�e par une pi�ce d'une m�me �quipe
				// ET qu'elle n'a la possibilit� que de manger une seule pi�ce.
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

void Rock::display(std::ostream& out) const {
	out << "R";
}
