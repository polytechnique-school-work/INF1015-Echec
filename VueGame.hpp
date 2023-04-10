#include <memory>
#include "Board.hpp"
namespace vue {
	class Game {
	public:
		static Game& getInstance();
		model::Location& getSelected();
	private:
		static std::unique_ptr<Game> $instance;
		model::Location selected;
	};
}