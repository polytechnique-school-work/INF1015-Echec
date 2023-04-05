#pragma once
#include <optional>
#include <memory>
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rock.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"

using namespace std;

static constexpr int BOARD_SIZE = 8;

using PieceContainer = optional<unique_ptr<Piece>>;
using BoardContainer = unique_ptr<unique_ptr<PieceContainer[]>[]>;

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