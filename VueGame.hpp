#include <memory>
#include <optional>
#include "Board.hpp"
namespace vue {
	class Game {
	public:
		static Game& getInstance();
		std::optional<model::Location>& getSelected();
		void setSelected(std::optional<model::Location> loc);
	private:
		static std::unique_ptr<Game> $instance;
		std::optional<model::Location> selected;
	};
}