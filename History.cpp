#include "History.hpp"
#include "Board.hpp"
#include "Game.hpp"

model::History::~History()
{


	std::cout << "Deplacement de " << **beforePiece << " vers ";
	(afterPiece.has_value() ? std::cout << **afterPiece : std::cout << "X");
	std::cout << std::endl;

	std::cout << "Delete" << std::endl;
	Board& board =  Board::getInstance();

	std::cout << board << std::endl;


	board.setPieceAt(this->beforePiece, before);
	board.setPieceAt(this->afterPiece, after);
	(**this->beforePiece).decrementMoves();
	Game::getInstance().nextTurn();

	std::cout << board << std::endl;
}

model::History::History(Location before, Location after) : before(before), after(after)
{
	std::cout << "Construct" << std::endl;
	BoardContainer& board = Board::getInstance().getBoardContainer();


	this->afterPiece = board[after.first][after.second];
	this->beforePiece = board[before.first][before.second];


	std::cout << "Deplacement de " << **beforePiece << " vers ";
	(afterPiece.has_value() ? std::cout << **afterPiece : std::cout << "X");
	std::cout << std::endl;
} 
