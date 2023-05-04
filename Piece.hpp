#pragma once
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <optional>
#include <memory>

namespace model {

	class Piece;

	using Location = std::pair<int, int>;
	using LocationContainer = std::list<Location>;
	using PieceContainer = std::optional<std::shared_ptr<Piece>>;
	using BoardContainer = std::unique_ptr<std::unique_ptr<PieceContainer[]>[]>;
	using Pieces = std::vector<PieceContainer>;

	std::ostream& operator<<(std::ostream& out, const LocationContainer& locations);
	std::ostream& operator<<(std::ostream& out, const Location& loc);
	std::ostream& operator<<(std::ostream& out, const PieceContainer& piece);

	enum class Team
	{
		BLACK, WHITE
	};

	class Piece {
	public:
		Piece(Team team) : team(team) {};
		Team getTeam();
		void incrementMoves();
		void decrementMoves();
		bool getMoves() const;
		virtual std::string getName() = 0;
		virtual LocationContainer getPossiblePositions(Location& loc) const = 0;
		virtual std::string getTag() = 0;
		virtual ~Piece() = default;
	protected:
		Team team;
	private:
		int moves = 0;
	};
}
