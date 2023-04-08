#pragma once
#include "Piece.hpp"
namespace model {

	class History
	{
	public:
		History(Location before, Location after);
		~History();
	private:
		PieceContainer beforePiece;

		PieceContainer afterPiece;

		Location before;

		Location after;
	};
}

