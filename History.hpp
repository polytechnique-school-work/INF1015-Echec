#pragma once
namespace model {

	class History
	{
		History();
		~History();
	private:
		char piece;

		// Le player qui a fait le déplacement
		char team;

		// L'emplacement initial de la pièce
		//Location before;

		// L'emplacement final de la pièce
		//Location after;
	};
}

