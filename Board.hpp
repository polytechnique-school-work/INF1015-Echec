#pragma once
#include <optional>
#include <memory>
#include <stack>
#include "Piece.hpp"
#include "History.hpp"


namespace model {

	static constexpr int BOARD_SIZE = 8;

	class Board {
	public:
		void movePiece(Location src, Location dst);
		std::list<Location> possibleMoves(Location src);

		PieceContainer& getPiece(Location src) const;
		Board();

		friend std::ostream& operator<<(std::ostream& out, const Board& board);

		std::list<Location> calculatePossiblePosition(Piece& piece, Location pos);

		std::list<Location> calculateKingSafePosition(Piece& piece, Location pos);

		void rollback();

		void generateBoard(const std::string& defaultBoard);

		// Savoir si le roi à sa position actuel est en danger.
		bool isEchec(Location& loc, Team& team);

		// Si le roi n'a pas de possibleMoves (faire en sorte de retirer les moves dangereux) ET s'il
		// n'est pas possible de manger une pièce qui permet un retour à la normal (et donc que le roi
		// n'est pas possible d'être mangé au prochain tour) ET si le roi est en échec.
		bool isMat(Location& loc, Team& team);

		PieceContainer pieceConverter(char color, char piece);
		static Board& getInstance();

		BoardContainer& getBoardContainer();

		std::list<Location> relativeToRealPosition(std::list<Location>& locations, Location pos);

		// Comment déterminer si le déplacement est safe : 
		// *	Aucun pion ne peut le manger après le déplacement aux coordonnées choisies.
		bool isSafeMove(Location& loc, Team& team);
		void removeUnsafeMove(std::list<Location>& possibleMoves, Team team);
		void removeSameTeamMove(std::list<Location>& possibleMoves, Team team);

		void printPiecePosition();
		void displaySelected(Location pos);
		void displayWithList(std::list<Location> positions);
		bool isMovePossible(Location src, Location dst);

	private:
		static std::unique_ptr<Board> $instance;
		BoardContainer board;
		Pieces pieces;

		std::stack<History> history;
	};

	std::ostream& operator<<(std::ostream& out, const Board& board);
}