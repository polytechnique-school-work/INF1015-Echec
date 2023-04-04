#pragma once
#include <string>
#include <iostream>
#include <list>
using Location = std::pair<int, int>;

enum class Team
{
	BLACK, WHITE
};

class Piece {
public:
	Piece(Team team) : team(team) {};
	Team getTeam();
	void setPieceMove();
	bool hasAlreadyMove();
	virtual std::list<Location> getPossiblePositions() const = 0;
	virtual void display(std::ostream& out) const = 0;
	friend std::ostream& operator<<(std::ostream& out, const Piece& piece);
	virtual ~Piece() = default;
protected:
	Team team;
private:
	bool hasMove = false;
};