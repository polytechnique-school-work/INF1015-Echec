#pragma once
#include <optional>
#include <memory>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rock.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"

using namespace std;

static constexpr int BOARD_SIZE = 8;



class Board {
public:
	void movePiece(Location src, Location dst);
	list<Location> possibleMoves(Location src);

	PieceContainer& getPiece(Location src) const;
	Board();

	friend std::ostream& operator<<(std::ostream& out, const Board& board);

	std::list<Location> calculatePossiblePosition(Location pos);
private:
	PieceContainer pieceConverter(char color, char piece);
	bool isMovePossible(Location src, Location dst);
	BoardContainer board;
};