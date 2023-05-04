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
		LocationContainer possibleMoves(Location src);

		PieceContainer& getPiece(Location src) const;
		Board();


		void rollback();

		void generateBoard(const std::string& defaultBoard);

		// Savoir si le roi à sa position actuel est en danger.
		bool isEchec(Team team);

		// Si le roi n'a pas de possibleMoves (faire en sorte de retirer les moves dangereux) ET s'il
		// n'est pas possible de manger une pièce qui permet un retour à la normal (et donc que le roi
		// n'est pas possible d'être mangé au prochain tour) ET si le roi est en échec.
		bool isMat(Team team);

		PieceContainer pieceConverter(char color, char piece);
		static Board& getInstance();

		BoardContainer& getBoardContainer();

		Location getKingLocation(Team& team);

		void removeTestedUnesafeLocation(Location& before, LocationContainer& possibleMovess);

		LocationContainer relativeToRealPosition(LocationContainer& locations, Location pos);

		// Comment déterminer si le déplacement est safe : 
		// *	Aucun pion ne peut le manger après le déplacement aux coordonnées choisies.
		bool isSafeMove(const Location& loc, Team& team);
		void removeUnsafeMove(LocationContainer& possibleMoves, Team team);

		LocationContainer getEveryDangerousPlaces(Team& team);

		bool isMovePossible(Location src, Location dst);

		std::string saveBoard();

		std::string convertPieceToBoard(PieceContainer& pieceContainer);

		void setPieceAt(PieceContainer& piece, Location loc);

		static int nbExecution;

	private:
		LocationContainer calculatePossiblePosition(Piece& piece, Location pos, bool remove);

		LocationContainer calculateKingSafePosition(Piece& piece, Location pos);

		static std::unique_ptr<Board> $instance;
		BoardContainer board;
		Pieces pieces;

		std::stack<std::unique_ptr<History>> history;
	};
}