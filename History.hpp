#pragma once
namespace model {

	class History
	{
		History();
		~History();
	private:
		char piece;

		// Le player qui a fait le d�placement
		char team;

		// L'emplacement initial de la pi�ce
		//Location before;

		// L'emplacement final de la pi�ce
		//Location after;
	};
}

