#include "Board.hpp"
#include "Board.hpp";
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rock.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include <iostream>

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
	// const std::string defaultBoard = "BRBCBFBQBKBFBCBRBPBPBPBPBPBPBPBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWPWPWPWPWPWPWPWPWRWCWFWQWKWFWCWR";
	//const std::string defaultBoard = "XXXXXXXXXXBFXXXXXXBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWKWPXXXXXXXXXXXXXXXXXXXXXXBCXXXXXXXXXXXXXXXXXXXXXXBRXXXXXXXXXXXXXXXXXXXXXX";
	const std::string defaultBoard = "XXXXXXXXXXBFXXXXXXBPXXXXXXXXXXXXXXXXWPXXXXXXXXXXXXXXXXWKWPXXXXXXXXXXXXXXXXXXXXXXBCXXXXXXXXXXXXXXXXXXXXXXBRXXXXXXXXXXXXXXXXXXXXXX";
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
// (x: " << j << " y: " << i << ")"
void model::Board::printPiecePosition()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[j][i].has_value()) {
				cout << typeid((**board[j][i])).name() << "\t" << Location(j, i) << endl;
			}
		}
	}
}

void model::Board::displaySelected(Location pos)
{
	static const string ligneDeSeparation = "\033[32m─────────────────────────────────────────────────────────────\033[0m\n";
	list<Location> selectedPiece = this->calculatePossiblePosition(pos);

	cout << ligneDeSeparation << endl;
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++) {
			auto&& piece = this->getPiece(Location(x, y));

			auto it = find(selectedPiece.begin(), selectedPiece.end(), Location(x, y));

			if (it != selectedPiece.end()) {
				cout << "\033[1;31m" << piece << "\033[0m";
			}
			else {
				cout << piece;
			}


			cout << "\t";
		}

		cout << endl;
	}

	cout << ligneDeSeparation << endl;

}


std::list<Location> Board::calculatePossiblePosition(Location pos)
{
	list<Location> relativePosition = (**getPiece(pos)).getPossiblePositions(pos);

	list<Location> positions = relativeToRealPosition(relativePosition, pos);
	Piece& piece = (**this->getPiece(pos));
	Team team = piece.getTeam();

	// Regarder si la pièce sélectionnée est de la même équipe
	positions.remove_if([&team, this](Location& location) {
		return (this->getPiece(location)).has_value() && team == (**(this->getPiece(location))).getTeam();
		});
	
	if (King* king = dynamic_cast<King*>(&piece)) {
		Board::getInstance().removeUnsafeMove(positions, king->getTeam());
	}

	return positions;
}

void model::Board::rollback()
{
	this->history.pop();
}

bool model::Board::isEchec(Location& loc, Team& team)
{
	return false;
}

bool model::Board::isMat(Location& loc, Team& team)
{
	return false;
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

list<Location> model::Board::relativeToRealPosition(list<Location>& relativePositions, Location pos)
{
	list<Location> positions = {};

	for (Location& loc : relativePositions) {

		// Calculer la location relative
		Location realLocation = { loc.first + pos.first, loc.second + pos.second };

		// Regarder si la pièce se situe à l'extérieur du tableau
		if (realLocation.first < 0 || realLocation.first > 8 || realLocation.second < 0 || realLocation.second > 8) continue;

		// Normalement tout devrait avoir été calculé
		positions.push_back(realLocation);
	}

	return positions;
}

bool Board::isSafeMove(Location& loc, Team& team)
{
	Team opponent = team == Team::WHITE ? Team::BLACK : Team::WHITE;

	// TODO : Faire des tests de rapidité, si ce serait pas plus rapide de faire 2 listes de vecteurs selon la team
	// et de les garder en variable static déjà déclaré et choisir en fonction de ce qu'on a besoin.
	vector<shared_ptr<Piece>> pieces = {
		make_shared<Queen>(Queen(opponent)),
		make_shared<Bishop>(Bishop(opponent)),
		make_shared<King>(King(opponent, true)),
		make_shared<Knight>(Knight(opponent)),
		make_shared<Rock>(Rock(opponent)),
		make_shared<Pawn>(Pawn(opponent)),
	};

	Board& board = Board::getInstance();
	for (shared_ptr<Piece>& piece : pieces) {

		list<Location> relativePositions = piece->getPossiblePositions(loc);
		list<Location> realPositions = board.relativeToRealPosition(relativePositions, loc);

		// Pour chacune de ces possibles positions, on regarde s'il y a une pièce à l'extrémité.
		for (Location& pos : realPositions) {

			// S'il y a une pièce du type de piece, alors ça veut dire que la loc est dangereuse.
			PieceContainer& possiblePiece = board.getPiece(pos);
			return !(possiblePiece.has_value() && (typeid(**possiblePiece) == typeid(*piece)) && ((**possiblePiece).getTeam() != piece->getTeam()));
		}
	}

	return true;
}

void Board::removeUnsafeMove(list<Location>& possibleMoves, Team team)
{
	possibleMoves.remove_if([this, &team](Location& move) { return !isSafeMove(move, team); });
}

void model::Board::removeSameTeamMove(std::list<Location>& possibleMoves, Team team)
{
	for (Location& location : possibleMoves) {
		PieceContainer& pieceAtLocationContainer = this->getPiece(location);
		if (pieceAtLocationContainer.has_value()) {
			Piece& pieceAtLocation = (**pieceAtLocationContainer);
			if (pieceAtLocation.getTeam() == team) possibleMoves.remove(location);
		}
	}
}
