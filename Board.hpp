#pragma once
#include <optional>
#include <memory>
#include <list>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"

using namespace std;

static constexpr int BOARD_SIZE = 8;

using Location = pair<int, int>;
using BoardArray = unique_ptr<unique_ptr<optional<unique_ptr<Piece>>[]>[]>;

class Board {
public:
	void movePiece(Location src, Location dst);
	list<Location> possibleMoves(Location loc);


	//template<typename T>
	optional<unique_ptr<Piece>>& getPiece(Location loc);
	Board();

private:
	BoardArray board;
};