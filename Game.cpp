#include "Game.hpp"
using namespace model;


void Game::nextTurn()
{
	// std::cout << "Changement d'equipe" << std::endl;
	this->turn = (this->turn == Team::WHITE ? Team::BLACK : Team::WHITE);
}

std::unique_ptr<Game> Game::$instance = nullptr;

Game& model::Game::getInstance()
{
	if ($instance == nullptr) {
		$instance = std::make_unique<Game>(Game());
	}
	return *$instance;
}

Team& model::Game::getTurn()
{
	return turn;
}

void model::Game::setTurn(Team team) {
	this->turn = team;
}
