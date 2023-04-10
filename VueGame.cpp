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

std::optional<model::Location>& vue::Game::getSelected()
{
	return selected;
}

void vue::Game::setSelected(std::optional<model::Location> loc)
{
	selected = loc;
}

