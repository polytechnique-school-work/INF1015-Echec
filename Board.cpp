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


	this->board[dst.first][dst.second] = move(this->board[src.first][src.second]);
	this->board[src.first][src.second] = {};
	(**this->getPiece(dst)).incrementMoves();
	this->history.push(History(src, dst));

	// TODO Compter les pièces et la retirer des pièces actives.
}

std::list<Location> Board::possibleMoves(Location src)
{
	// TODO :	Faire un nettoyage des positions renvoyées par les pièces
	//			pour éliminer les coordonnées qui sont en dehors du jeu
	//			et celles qui sont pas possibles.
 
	PieceContainer& piece = this->getPiece(src);
	Board& board = Board::getInstance();
	return board.calculateKingSafePosition(**piece, src);
}




Board::Board()
{
	// Bon c'est la méthode la moins dégueulasse que j'ai trouvé pour placer les pions.
	// const std::string defaultBoard = "XXXXXXXXXXBFXXXXXXBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWKWPXXXXXXXXXXXXXXXXXXXXXXBCXXXXXXXXXXXXXXXXXXXXXXBRXXXXXXXXXXXXXXXXXXXXXX";
	// const std::string defaultBoard = "XXXXXXXXXXBFXXXXXXBPXXXXXXXXXXXXXXXXWPXXXXXXXXXXXXXXXXWKWPXXXXXXXXXXXXXXXXXXXXXXBCXXXXXXXXXXXXXXXXXXXXXXBRXXXXXXXXXXXXXXXXXXXXXX";
	// generateBoard(defaultBoard);
}

bool Board::isMovePossible(Location src, Location dst)
{
	std::list<Location> possibleMoves = this->possibleMoves(src);
	auto it = find(possibleMoves.begin(), possibleMoves.end(), dst);
	return it != possibleMoves.end();
}


std::list<Location> Board::calculatePossiblePosition(Piece& piece, Location pos)
{
	list<Location> relativePosition = piece.getPossiblePositions(pos);

	list<Location> positions = relativeToRealPosition(relativePosition, pos);
	Team team = piece.getTeam();

	// Regarder si la pièce sélectionnée est de la même équipe
	positions.remove_if([&team, this](Location& location) {
		return (this->getPiece(location)).has_value() && team == (**(this->getPiece(location))).getTeam();
		});

	return positions;
}

std::list<Location> model::Board::calculateKingSafePosition(Piece& piece, Location pos)
{
	list<Location> locations =  calculatePossiblePosition(piece, pos);

	if (King* king = dynamic_cast<King*>(&piece)) {
		Board::getInstance().removeUnsafeMove(locations, king->getTeam());
	}
	return locations;
}

void model::Board::rollback()
{
	this->history.pop();
}

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
		if (realLocation.first < 0 || realLocation.first > BOARD_SIZE || realLocation.second < 0 || realLocation.second > BOARD_SIZE) continue;

		// Normalement tout devrait avoir été calculé
		positions.push_back(realLocation);
	}

	return positions;
}

bool Board::isSafeMove(Location& loc, Team& team)
{
	// Team opponent = team == Team::WHITE ? Team::BLACK : Team::WHITE;

	// TODO : Faire des tests de rapidité, si ce serait pas plus rapide de faire 2 listes de vecteurs selon la team
	// et de les garder en variable static déjà déclaré et choisir en fonction de ce qu'on a besoin.
	vector<shared_ptr<Piece>> pieces = {
		make_shared<Queen>(Queen(team)),
		make_shared<Bishop>(Bishop(team)),
		make_shared<King>(King(team, true)),
		make_shared<Knight>(Knight(team)),
		make_shared<Rock>(Rock(team)),
		make_shared<Pawn>(Pawn(team)),
	};

	Board& board = Board::getInstance();
	for (shared_ptr<Piece>& piece : pieces) {

		list<Location> realPositions = board.calculatePossiblePosition(*piece, loc);// piece->getPossiblePositions(loc);

		// Pour chacune de ces possibles positions, on regarde s'il y a une pièce à l'extrémité.
		for (Location& pos : realPositions) {

			// S'il y a une pièce du type de piece, alors ça veut dire que la loc est dangereuse.
			// cout << pos << endl;
			PieceContainer& possiblePiece = board.getPiece(pos);

			// On regarde si la position contient une pièce.
			if (possiblePiece.has_value()) {
				Piece& selectedPiece = **possiblePiece;
				// Si les deux pièces sont du même type, on s'en fou. Elle devrait pas le manger.
				if (selectedPiece.getTeam() != piece->getTeam()) {
					// Si les types des pièces sont les mêmes, y'a présence de danger.
					if (typeid(selectedPiece) == typeid(*piece)) {
						return false;
					}
				}
			}
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



/*

	PRINTER : Surtout pour du débug

*/

void model::Board::printPiecePosition()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[j][i].has_value()) {
				cout << typeid((**board[j][i])).name() << "\t" << Location(j, i) << endl;
			}
		}
	}
}

void model::Board::displaySelected(Location pos)
{
	static const string ligneDeSeparation = "\033[32m─────────────────────────────────────────────────────────────\033[0m\n";

	Piece& piece = **this->getPiece(pos);
	list<Location> selectedPiece = this->calculateKingSafePosition(piece, pos);

	cout << ligneDeSeparation << endl;
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++) {
			auto&& piece = this->getPiece(Location(x, y));

			auto it = find(selectedPiece.begin(), selectedPiece.end(), Location(x, y));

			if (it != selectedPiece.end()) {
				cout << "\033[1;31m[\033[0m" << piece << "\033[1;31m]\033[0m";
			}
			else {
				cout << "\033[1;90m[\033[0m" << piece << "\033[1;90m]\033[0m";
			}


			cout << "\t";
		}

		cout << endl;
	}

	cout << ligneDeSeparation << endl;

}

void model::Board::displayWithList(list<Location> positions)
{
	static const string ligneDeSeparation = "\033[32m─────────────────────────────────────────────────────────────\033[0m\n";


	cout << ligneDeSeparation << endl;
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++) {
			auto&& piece = this->getPiece(Location(x, y));

			auto it = find(positions.begin(), positions.end(), Location(x, y));

			if (it != positions.end()) {
				cout << "\033[1;31m[\033[0m" << piece << "\033[1;31m]\033[0m";
			}
			else {
				cout << "\033[1;90m[\033[0m" << piece << "\033[1;90m]\033[0m";
			}


			cout << "\t";
		}

		cout << endl;
	}

	cout << ligneDeSeparation << endl;
}