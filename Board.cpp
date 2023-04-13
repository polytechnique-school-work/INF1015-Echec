﻿#include "Board.hpp"
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

// Obtenir une pièce grâce à une position src
PieceContainer& Board::getPiece(Location src) const {
	return this->board[src.first][src.second];
}

// Déplacer une pièce d'une position src à dst
void Board::movePiece(Location src, Location dst)
{
	this->board[dst.first][dst.second] = move(this->board[src.first][src.second]);
	this->board[src.first][src.second] = {};
	(**this->getPiece(dst)).incrementMoves();
	this->history.push(unique_ptr<History>(new History(src, dst)));
}

// Obtenir les déplacements possibles pour une pièce à la position src
LocationContainer Board::possibleMoves(Location src)
{
	LocationContainer locations = {};
	PieceContainer& piece = this->getPiece(src);
	if (piece.has_value()) {
		Board& board = Board::getInstance();
		locations = board.calculateKingSafePosition(**piece, src);
	}
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

// Retirer les positions éronnées (qui sont en dehors du tableau de jeu)
void model::Board::removeErronedLocations(LocationContainer& locations)
{
	std::remove_if(locations.begin(), locations.end(), [&](const Location& location) { return location.first < 0 || location.first >= BOARD_SIZE || location.second < 0 || location.second >= BOARD_SIZE; });
}

// Calculer les déplacements possibles
LocationContainer Board::calculatePossiblePosition(Piece& piece, Location pos)
{
	LocationContainer relativePosition = piece.getPossiblePositions(pos);
	LocationContainer positions = relativeToRealPosition(relativePosition, pos);

	Team team = piece.getTeam();

	// Retirer si la pièce sélectionnée est de la même équipe
	positions.remove_if([&team, this](const Location& location) {return (this->getPiece(location)).has_value() && team == (**(this->getPiece(location))).getTeam(); });

	return positions;
}

// Calculer les déplacements possibles en sécurisant le roi
LocationContainer model::Board::calculateKingSafePosition(Piece& piece, Location pos)
{
	LocationContainer locations =  calculatePossiblePosition(piece, pos);

	if (King* king = dynamic_cast<King*>(&piece)) {
		Board::getInstance().removeUnsafeMove(locations, king->getTeam());
	}
	return locations;
}

// Permettre un retour en arrière du jeu (c'est le RAII)
void model::Board::rollback()
{
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
}

// Vérifier si le roi est en échec
bool model::Board::isEchec(Location& loc, Team& team)
{
	return false;
}

// Vérifier si le roi est en échec et mat
bool model::Board::isMat(Location& loc, Team& team)
{
	return false;
}

// Permet de convertir les pièces du board en objet
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

bool Board::isSafeMove(const Location& loc, Team& team)
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

		LocationContainer realPositions = board.calculatePossiblePosition(*piece, loc);// piece->getPossiblePositions(loc);

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

void Board::removeUnsafeMove(LocationContainer& possibleMoves, Team team)
{
	possibleMoves.remove_if([&](const Location& location) {return !isSafeMove(location, team); });
}

void model::Board::removeSameTeamMove(LocationContainer& possibleMoves, Team team)
{
	for (Location& location : possibleMoves) {
		PieceContainer& pieceAtLocationContainer = this->getPiece(location);
		if (pieceAtLocationContainer.has_value()) {
			Piece& pieceAtLocation = (**pieceAtLocationContainer);
			if (pieceAtLocation.getTeam() == team)
				possibleMoves.remove(location);
		}
	}
}