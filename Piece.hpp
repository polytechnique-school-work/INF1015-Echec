#pragma once
#include <string>
#include <iostream>
#include <list>
#include <optional>
#include <memory>

namespace model {

	class Piece;

	using Location = std::pair<int, int>;
	using PieceContainer = std::optional<std::unique_ptr<Piece>>;
	using BoardContainer = std::unique_ptr<std::unique_ptr<PieceContainer[]>[]>;

	enum class Team
	{
		BLACK, WHITE
	};

	class Piece {
	public:
		Piece(Team team) : team(team) {};
		Team getTeam();
		void setPieceMove();
		bool hasAlreadyMove() const;
		virtual std::list<Location> getPossiblePositions(BoardContainer* board, Location& loc) const = 0;
		virtual void display(std::ostream& out) const = 0;
		friend std::ostream& operator<<(std::ostream& out, const Piece& piece);
		virtual ~Piece() = default;
	protected:
		Team team;
	private:
		bool hasMove = false;
	};

}