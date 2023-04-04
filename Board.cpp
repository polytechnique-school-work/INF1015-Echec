#include "Board.hpp"

PieceContainer& Board::getPiece(Location src) {
	return this->board[src.first][src.second];
}



void Board::movePiece(Location src, Location dst)
{
	if (!isMovePossible(src, dst)) return; // Ne devrait jamais être run, enlever si non nécessaire.

	this->getPiece(dst) = move(this->getPiece(src));
	this->getPiece(src) = {};

	(**this->getPiece(src)).setPieceMove();



	// TODO Compter les pièces et la retirer des pièces actives.
}

std::list<Location> Board::possibleMoves(Location src)
{
	// TODO

	PieceContainer& piece = this->getPiece(src);
	return (**piece).getPossiblePositions();
}

Board::Board()
{
	// Initialisation d'un tableau de 8x8 cases.
	// Tous les éléments sont en fait des nullopt.
	this->board = make_unique<unique_ptr<PieceContainer[]>[]>(8);
	for (int i = 0; i < 8; ++i)
		board[i] = make_unique<PieceContainer[]>(8);

	board[0][0] = move(make_unique<Pawn>());
	board[0][1] = move(make_unique<King>());
}

bool Board::isMovePossible(Location src, Location dst)
{
	std::list<Location> possibleMoves = this->possibleMoves(src);
	auto it = std::find(possibleMoves.begin(), possibleMoves.end(), dst);
	return it != possibleMoves.end();
}
