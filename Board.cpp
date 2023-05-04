#include "Board.hpp"
#include "Board.hpp";
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rock.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Game.hpp"
#include <iostream>


using namespace std;

namespace model {

	int Board::nbExecution = 0;

	// Obtenir une pièce grâce à une position src
	PieceContainer& Board::getPiece(Location src) const {
		nbExecution++;
		return this->board[src.first][src.second];
	}

	// Déplacer une pièce d'une position src à dst
	void Board::movePiece(Location src, Location dst)
	{
		model::Game& modelGame = model::Game::getInstance();
		this->history.push(unique_ptr<History>(new History(src, dst)));
		this->board[dst.first][dst.second] = move(this->board[src.first][src.second]);
		this->board[src.first][src.second] = {};
		(**this->getPiece(dst)).incrementMoves();
		modelGame.nextTurn();
	}

	// Obtenir les déplacements possibles pour une pièce à la position src
	LocationContainer Board::possibleMoves(Location src)
	{
		LocationContainer locations = {};
		PieceContainer& piece = this->getPiece(src);
		if (piece.has_value()) {
			locations = calculateKingSafePosition(**piece, src);
		}

		// Retrait des positions si y'a possibilité d'échec
		removeTestedUnesafeLocation(src, locations);

		return locations;
	}

	Board::Board() {}

	// Vérifier si un déplacement est possible => Non utilisé pour le moment
	bool Board::isMovePossible(Location src, Location dst)
	{
		LocationContainer possibleMoves = this->possibleMoves(src);
		auto it = find(possibleMoves.begin(), possibleMoves.end(), dst);
		return it != possibleMoves.end();
	}

	std::string model::Board::saveBoard()
	{
		string value = "";
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				value += convertPieceToBoard(board[j][i]);
			}
		}
		return value;
	}

	string Board::convertPieceToBoard(PieceContainer& pieceContainer) {
		if (!pieceContainer.has_value()) return "XX";
		Piece& piece = **pieceContainer;
		return (piece.getTeam() == Team::WHITE ? "W" : "B") + piece.getTag();
	}

	void model::Board::setPieceAt(PieceContainer& piece, Location loc)
	{
		// cout << "Changement de position de la pièce" << endl;
		board[loc.first][loc.second] = piece;
	}

	// Calculer les déplacements possibles
	LocationContainer Board::calculatePossiblePosition(Piece& piece, Location pos, bool remove = false)
	{
		LocationContainer relativePosition = piece.getPossiblePositions(pos);

		if (Pawn* pawn = dynamic_cast<Pawn*>(&piece)) {
			if (remove) {
				pawn->removeForwardDirection(pos, relativePosition);
			}
			else {
				pawn->removeEatPosition(pos, relativePosition);
			}

		}


		LocationContainer positions = relativeToRealPosition(relativePosition, pos);

		Team team = piece.getTeam();

		// Retirer si la pièce sélectionnée est de la même équipe
		positions.remove_if([&team, this](const Location& location) {return (this->getPiece(location)).has_value() && team == (**(this->getPiece(location))).getTeam(); });

		return positions;
	}

	Location Board::getKingLocation(Team& team) {
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (board[j][i].has_value() && typeid(**board[j][i]) == typeid(King) && (**board[j][i]).getTeam() == team) return { j, i };
			}
		}
		return {};
		// throw logic_error("Impossible de trouver le roi");
	}

	void model::Board::removeTestedUnesafeLocation(Location& before, LocationContainer& possibleMoves)
	{
		LocationContainer newLocationContainer = possibleMoves;
		Team team = (**this->getPiece(before)).getTeam();
		for (const Location& after : newLocationContainer) {
			movePiece(before, after);
			if (isEchec(team)) possibleMoves.remove(after);
			rollback();
		}
	}


	// Calculer les déplacements possibles en sécurisant le roi
	LocationContainer model::Board::calculateKingSafePosition(Piece& piece, Location pos)
	{
		LocationContainer locations = calculatePossiblePosition(piece, pos);

		if (King* king = dynamic_cast<King*>(&piece)) {
			Board::getInstance().removeUnsafeMove(locations, king->getTeam());
		}
		return locations;
	}



	// Permettre un retour en arrière du jeu (c'est le RAII)
	void model::Board::rollback()
	{
		if (!this->history.empty())
			this->history.pop();
	}

	// Permet de générer un board
	void model::Board::generateBoard(const std::string& defaultBoard)
	{
		if (defaultBoard.size() != static_cast<unsigned long long>(BOARD_SIZE) * BOARD_SIZE * 2) throw logic_error("Le defaultBoard doit être de BOARD_SIZE * BOARD_SIZE cases.");

		// Reset des pièces.
		this->pieces = Pieces();

		// Initialisation d'un tableau de 8x8 cases.
		// Tous les éléments sont en fait des nullopt.
		this->board = std::make_unique<std::unique_ptr<PieceContainer[]>[]>(8);
		for (int i = 0; i < 8; ++i)
			board[i] = std::make_unique<PieceContainer[]>(8);

		int actual = 0;
		for (int y = 0; y < BOARD_SIZE; ++y) {
			for (int x = 0; x < BOARD_SIZE; ++x) {
				// Le gros truc bizarre c'est une proposition de l'IDE
				PieceContainer piece = this->pieceConverter(defaultBoard[actual], defaultBoard[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(actual) + 1]);
				board[x][y] = piece;
				this->pieces.push_back(piece);
				actual += 2;
			}
		}

		this->history = stack<std::unique_ptr<History>>();
	}

	// Vérifier si le roi est en échec
	bool model::Board::isEchec(Team team)
	{
		LocationContainer locations = getEveryDangerousPlaces(team);
		Location loc = getKingLocation(team);
		auto&& it = find(locations.begin(), locations.end(), loc);
		return it != locations.end();
	}

	// Vérifier si le roi est en échec et mat
	bool model::Board::isMat(Team team)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			for (int x = 0; x < BOARD_SIZE; x++)
			{
				PieceContainer& pieceCtr = getPiece({ x,y });
				if (!pieceCtr.has_value()) continue;
				Piece& piece = **pieceCtr;
				if (piece.getTeam() != team) continue;

				LocationContainer locations = possibleMoves({ x,y });
				if (locations.size() != 0) return false;
			}
		}

		return true;
	}

	// Permet de convertir les pièces du board en objet
	PieceContainer Board::pieceConverter(char color, char piece) {

		Team team = color == 'W' ? Team::WHITE : Team::BLACK;

		switch (piece)
		{
		case 'F': // Bishop
			return make_unique<Bishop>(Bishop(team));
		case 'P': // Pawn
			return make_unique<Pawn>(Pawn(team));
		case 'K': // King
			return make_unique<King>(King(team));
		case 'Q': // Queen
			return make_unique<Queen>(Queen(team));
		case 'R': // Rook
			return make_unique<Rock>(Rock(team));
		case 'C': // Knight
			return make_unique<Knight>(Knight(team));
		case 'X': // No pieces
			return {};
		default:
			return {};
			break;
		}
	}

	unique_ptr<Board> Board::$instance = nullptr;

	Board& Board::getInstance()
	{
		if ($instance == nullptr) {
			$instance = make_unique<Board>(Board());
		}
		return *$instance;
	}

	BoardContainer& Board::getBoardContainer()
	{
		return this->board;
	}

	LocationContainer model::Board::relativeToRealPosition(LocationContainer& relativePositions, Location pos)
	{
		LocationContainer positions = {};

		for (Location& loc : relativePositions) {

			// Calculer la location relative
			Location realLocation = { loc.first + pos.first, loc.second + pos.second };

			// Regarder si la pièce se situe à l'extérieur du tableau
			if (realLocation.first < 0 || realLocation.first >= BOARD_SIZE || realLocation.second < 0 || realLocation.second >= BOARD_SIZE) continue;

			// Normalement tout devrait avoir été calculé
			positions.push_back(realLocation);
		}

		return positions;
	}

	LocationContainer Board::getEveryDangerousPlaces(Team& team) {
		LocationContainer locations = {};
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			for (int x = 0; x < BOARD_SIZE; x++)
			{
				if (!isSafeMove({ x, y }, team)) {
					locations.push_back({ x, y });
				}
			}
		}

		return locations;
	}

	/*
	* Prend en paramètre une team et une location.
	* Vérifie si la position loc est safe pour l'équipe team.
	**/
	bool Board::isSafeMove(const Location& loc, Team& team)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			for (int x = 0; x < BOARD_SIZE; x++)
			{
				Location checkedPieceLocation = { x, y };

				// Pour chacune des pièces, on regarde si la pièce représente un danger.
				PieceContainer& pieceCtr = this->board[x][y];
				if (!pieceCtr.has_value()) continue;
				Piece& piece = **pieceCtr;
				if (piece.getTeam() == team) continue;
				LocationContainer locations = calculatePossiblePosition(piece, checkedPieceLocation, true);

				// On regarde les positions possibles d'une pièce peut atteindre loc
				for (const Location& checkLocation : locations) {
					if (checkLocation == loc) {
						// cout << "La pièce " << piece << " " << checkedPieceLocation << " représente un danger pour l'emplacement " << loc << "." << endl;
						return false;
					}
				}

			}
		}
		return true;
	}

	void Board::removeUnsafeMove(LocationContainer& possibleMoves, Team team)
	{
		possibleMoves.remove_if([&](const Location& location) {return !isSafeMove(location, team); });
	}

}