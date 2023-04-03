#include "Board.hpp"

template<typename T>
optional<T>& Board::getPiece(Location loc) {
	auto& piece = this->board[loc.first][loc.second];
	auto typedPiece = dynamic_cast<T*>(piece.get());
	if (typedPiece) {
		return *typedPiece;
	}
	else {
		return optional<T> {};
	}
}

void Board::movePiece(Location src, Location dst)
{
	// TODO
}

list<Location> Board::possibleMoves(Location loc)
{
	// TODO
	return list<Piece>();
}
