enum class Team
{
	BLACK, WHITE
};

class Piece {
public:
	virtual void getPossiblePositions();
	Team getTeam();
private:
	Team team;
};