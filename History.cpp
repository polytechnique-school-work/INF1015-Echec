#include "History.hpp"
#include "Board.hpp"

model::History::~History()
{
	BoardContainer& board =  Board::getInstance().getBoardContainer();
	board[this->after.first][this->after.second] = this->beforePiece;
	board[this->before.first][this->before.second] = this->afterPiece;
	(**this->beforePiece).decrementMoves();
}

model::History::History(Location before, Location after) : before(before), after(after)
{
	BoardContainer& board = Board::getInstance().getBoardContainer();
	this->afterPiece = board[before.first][before.second];
	this->beforePiece = board[after.first][after.second];
} 
