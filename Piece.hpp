#pragma once
#include <string>
#include <iostream>
enum class Team
{
	BLACK, WHITE
};

class Piece {
public:
	//Piece(Team team, string name) : team(team), name(name) {};
	Team getTeam();
	virtual void getPossiblePositions() const = 0;
	virtual void display(std::ostream& out) const = 0;
	friend std::ostream& operator<<(std::ostream& out, const Piece& piece);
	virtual ~Piece() = default;
private:
	Team team;
};