#include "Board.hpp"

//template<typename T>
optional<unique_ptr<Piece>>& Board::getPiece(Location loc) {
	return this->board[loc.first][loc.second];
	/*auto&& typedPiece = dynamic_cast<T*>(piece->get());
	if (typedPiece) {
		return *typedPiece;
	}
	else {
		return {};
	}*/
}


void Board::movePiece(Location src, Location dst)
{
	 // TODO
}

list<Location> Board::possibleMoves(Location loc)
{
	// TODO
	return list<Location>();
}

Board::Board()
{
	// Initialisation d'un tableau de 8x8 cases.
	// Tous les éléments sont en fait des nullopt.
	this->board = make_unique<unique_ptr<optional<unique_ptr<Piece>>[]>[]>(8);
	for (int i = 0; i < 8; ++i)
		board[i] = make_unique<optional<unique_ptr<Piece>>[]>(8);

	board[0][0] = move(make_unique<Pawn>());
	board[0][1] = move(make_unique<King>());
}
