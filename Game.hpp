#include "Board.hpp"

class Game {
public:
	void nextTurn();
private:
	Team turn = Team::WHITE;
};