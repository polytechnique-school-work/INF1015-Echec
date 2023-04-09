#include "Game.hpp"
using namespace model;


void Game::nextTurn()
{
	this->turn = this->turn == Team::WHITE ? Team::BLACK : Team::WHITE;
}

std::unique_ptr<Game> Game::$instance = nullptr;

Game& model::Game::getInstance()
{
	if ($instance == nullptr) {
		$instance = std::make_unique<Game>(Game());
	}
	return *$instance;
}
