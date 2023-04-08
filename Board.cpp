#include "Board.hpp"
#include "Board.hpp";
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rock.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"

using namespace std;
using namespace model;

PieceContainer& Board::getPiece(Location src) const {
	return this->board[src.first][src.second];
}



void Board::movePiece(Location src, Location dst)
{
	// Ne devrait jamais être run, enlever si non nécessaire.
	//if (!isMovePossible(src, dst)) {
	//	cout << "> Mouvement impossible" << endl;
	//	return;
	//}

	this->history.push(History(src, dst));

	this->board[dst.first][dst.second] = move(this->board[src.first][src.second]);
	this->board[src.first][src.second] = {};
	(**this->getPiece(dst)).incrementMoves();

	// TODO Compter les pièces et la retirer des pièces actives.
}

std::list<Location> Board::possibleMoves(Location src)
{
	// TODO :	Faire un nettoyage des positions renvoyées par les pièces
	//			pour éliminer les coordonnées qui sont en dehors du jeu
	//			et celles qui sont pas possibles.
 
	PieceContainer& piece = this->getPiece(src);
	return (**piece).getPossiblePositions(src);
}

Board::Board()
{
	// Bon c'est la méthode la moins dégueulasse que j'ai trouvé pour placer les pions.
	const std::string defaultBoard = "BRBCBFBQBKBFBCBRBPBPBPBPBPBPBPBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWPWPWPWPWPWPWPWPWRWCWFWQWKWFWCWR";

	// Initialisation d'un tableau de 8x8 cases.
	// Tous les éléments sont en fait des nullopt.
	this->board = std::make_unique<std::unique_ptr<PieceContainer[]>[]>(8);
	for (int i = 0; i < 8; ++i)
		board[i] = std::make_unique<PieceContainer[]>(8);

	int actual = 0;
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			// Le gros truc bizarre c'est une proposition de l'IDE
			PieceContainer piece = this->pieceConverter(defaultBoard[actual], defaultBoard[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(actual) + 1]);
			board[x][y] = piece;
			this->pieces.push_back(piece);
			actual += 2;
		}
	}
}

bool Board::isMovePossible(Location src, Location dst)
{
	std::list<Location> possibleMoves = this->possibleMoves(src);
	auto it = find(possibleMoves.begin(), possibleMoves.end(), dst);
	return it != possibleMoves.end();
}


std::list<Location> Board::calculatePossiblePosition(Location pos)
{
	Piece& piece = (**this->getPiece(pos));

	cout << piece << endl;

	list<Location> positions = {};
	
	list<Location> relativePosition = piece.getPossiblePositions(pos);

	for (Location& loc : relativePosition) {
		Location realLocation = { loc.first + pos.first, loc.second + pos.second };

		// Regarder si la pièce se situe à l'extérieur du tableau
		if (realLocation.first < 0 || realLocation.first > 8 || realLocation.second < 0 || realLocation.second > 8) continue;

		// Regarder si la pièce sélectionnée est de la même équipe
		PieceContainer& pieceAtLocationContainer = this->getPiece(realLocation);
		if (pieceAtLocationContainer.has_value()) {
			Piece& pieceAtLocation = (**pieceAtLocationContainer);
			if (pieceAtLocation.getTeam() == piece.getTeam()) continue;
		}

		// Normalement tout devrait avoir été calculé
		positions.push_back(realLocation);
	}

	return positions;
}

void model::Board::rollback()
{
	this->history.pop();
}

PieceContainer Board::pieceConverter(char color, char piece) {
	/*
	Bishop = F
	Pawn = P
	King = K
	Queen = Q
	Rock = R
	Knight = C

	Black = B
	White = W
	*/
	Team team = color == 'W' ? Team::WHITE : Team::BLACK;

	switch (piece)
	{
	case 'F':
		return make_unique<Bishop>(Bishop(team));
	case 'P':
		return make_unique<Pawn>(Pawn(team));
	case 'K':
		return make_unique<King>(King(team));
	case 'Q':
		return make_unique<Queen>(Queen(team));
	case 'R':
		return make_unique<Rock>(Rock(team));
	case 'C':
		return make_unique<Knight>(Knight(team));
	case 'X':
		return {};
	default:
		return {};
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

BoardContainer& const Board::getBoardContainer()
{
	return this->board;
}
