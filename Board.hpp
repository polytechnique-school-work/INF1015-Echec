#pragma once
#include <optional>
#include <memory>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rock.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"

namespace model {

	static constexpr int BOARD_SIZE = 8;

	class Board {
	public:
		void movePiece(Location src, Location dst);
		std::list<Location> possibleMoves(Location src);

		PieceContainer& getPiece(Location src) const;
		Board();

		friend std::ostream& operator<<(std::ostream& out, const Board& board);

		std::list<Location> calculatePossiblePosition(Location pos);

		bool isEchec();

		// Si le roi n'a pas de possibleMoves (faire en sorte de retirer les moves dangereux) ET s'il
		// n'est pas possible de manger une pièce qui permet un retour à la normal (et donc que le roi
		// n'est pas possible d'être mangé au prochain tour).
		bool isMat();


	private:
		PieceContainer pieceConverter(char color, char piece);
		bool isMovePossible(Location src, Location dst);
		BoardContainer board;
	};

}