#include "Game.hpp"

void Game::nextTurn()
{
	this->turn = this->turn == Team::WHITE ? Team::BLACK : Team::WHITE;
}
