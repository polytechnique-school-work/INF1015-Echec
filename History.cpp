#include "History.hpp"
#include "Board.hpp"
#include "Game.hpp"

model::History::~History()
{
	std::cout << "Deplacement de " << afterPiece << " vers " << beforePiece << std::endl;
	Board& board =  Board::getInstance();

	board.setPieceAt(this->beforePiece, before);
	board.setPieceAt(this->afterPiece, after);
	(**this->beforePiece).decrementMoves();
	Game::getInstance().nextTurn();
}

model::History::History(Location before, Location after) : before(before), after(after)
{
	BoardContainer& board = Board::getInstance().getBoardContainer();
	this->afterPiece = board[after.first][after.second];
	this->beforePiece = board[before.first][before.second];
	std::cout << "Deplacement de " << beforePiece << " vers " << afterPiece << std::endl;
} 
