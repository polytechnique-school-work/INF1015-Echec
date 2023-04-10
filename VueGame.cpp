#include "VueGame.hpp"
using namespace vue;

std::unique_ptr<Game> Game::$instance = nullptr;

Game& vue::Game::getInstance()
{
	if ($instance == nullptr) {
		$instance = std::make_unique<Game>(Game());
	}
	return *$instance;
}

model::Location& vue::Game::getSelected()
{
	return selected;
}
