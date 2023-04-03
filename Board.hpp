#include <optional>
#include <memory>
#include <list>
#include "Piece.hpp"

using namespace std;

static constexpr int BOARD_SIZE = 8;

class Board {
public:
	void movePiece();
	list<Piece> possibleMoves();


	template<typename T>
	optional<T>& getPiece(int x, int y);
private:
	unique_ptr<unique_ptr<optional<Piece>[BOARD_SIZE]>[BOARD_SIZE]> board;
};