#pragma once
#include <optional>
#include <memory>
#include "Pawn.hpp"
#include "King.hpp"

using namespace std;

static constexpr int BOARD_SIZE = 8;

using PieceContainer = optional<unique_ptr<Piece>>;
using BoardContainer = unique_ptr<unique_ptr<PieceContainer[]>[]>;

class Board {
public:
	void movePiece(Location src, Location dst);
	list<Location> possibleMoves(Location src);

	PieceContainer& getPiece(Location src);
	Board();

private:
	bool isMovePossible(Location src, Location dst);
	BoardContainer board;
};