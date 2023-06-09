﻿#include "Rock.hpp"
#include "Board.hpp";

using namespace model;
using namespace std;

LocationContainer Rock::getPossiblePositions(Location& loc) const
{
	LocationContainer locations = {};

	LocationContainer possiblesMoves = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

	for (Location& location : possiblesMoves) {
		for (int i = 1; i < BOARD_SIZE; i++) {
			Location relative = {location.first * i, location.second * i};
			Location real = { relative.first + loc.first, relative.second + loc.second};

			if (real.first < 0 || real.first >= BOARD_SIZE || real.second < 0 || real.second >= BOARD_SIZE) {
				continue;
			}

			PieceContainer& pieceCtr = Board::getInstance().getBoardContainer()[real.first][real.second];
			// On ajoute la pièce seulement si et seulement si
			// La pièce n'est pas limitée par une pièce d'une même équipe
			// ET qu'elle n'a la possibilité que de manger une seule pièce.
			if (pieceCtr.has_value()) {
				Piece& piece = **pieceCtr;
				if (piece.getTeam() != this->team) locations.push_back({ relative.first, relative.second });
				break;
			}
			locations.push_back({ relative.first, relative.second });
		}
	}
	return locations;
}

// Pas dans les lignes couvertes par les tests : utile pour la vue
std::string model::Rock::getName()
{
	return "rock";
}

std::string model::Rock::getTag()
{
	return "R";
}
