/*
	Classe abstraite
*/


enum class Team
{
	BLACK, WHITE
};

class Piece {
public:
	virtual void getPossiblePositions() = 0;
	Team getTeam();
private:
	Team team;
};