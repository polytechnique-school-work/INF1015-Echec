#include "Board.hpp"

template<typename T>
optional<T>& Board::getPiece(int x, int y) {
	auto& piece = this->board[x][y];
	auto typedPiece = dynamic_cast<T*>(piece.get());
	if (typedPiece) {
		return *typedPiece;
	}
	else {
		return optional<T> {};
	}
}