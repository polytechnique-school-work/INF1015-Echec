#include <optional>
#include <memory>
#include <list>
#include "Piece.hpp"

using namespace std;

static constexpr int BOARD_SIZE = 8;

using Location = pair<int, int>;

class Board {
public:
	void movePiece(Location src, Location dst);
	list<Location> possibleMoves(Location loc);


	template<typename T>
	optional<T>& getPiece(Location loc);
private:
	unique_ptr<unique_ptr<optional<Piece>[BOARD_SIZE]>[BOARD_SIZE]> board;
};