#include <QApplication>

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

#include <iostream>
#include "Board.hpp"
#include "King.hpp"

#include "ChessWindow.hpp"



void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	// cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.
	
	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
	#endif
	//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main après l'appel à cette fonction puisqu'il exécute uniquement les tests Google Test dans l'appel ci-dessus.
}

void executer() {
	using namespace model;
	Board& board = Board::getInstance();
	const std::string defaultBoard = "BRBCBFBQBKBFBCBRBPBPBPBPBPBPBPBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWPWPWPWPWPWPWPWPWRWCWFWQWKWFWCWR";
	board.generateBoard(defaultBoard);
}



int main(int argc, char *argv[])
{
	using namespace vue;

	/*model::Piece* piece1 = nullptr;
	model::Piece* piece2 = nullptr;
	model::Piece* piece3 = nullptr;

	try
	{
		piece1 = new model::King(model::Team::WHITE);
		piece2 = new model::King(model::Team::BLACK);
		piece3 = new model::King(model::Team::WHITE);
		std::cout << "Nothing throw, executed" << std::endl;
	}
	catch (const std::logic_error& e)
	{
		delete piece1;
		delete piece2;
		delete piece3;
		std::cout << e.what() << std::endl;
	}*/


	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	initialiserBibliothequeCours(argc, argv);

	executer();
	ChessWindow chessWindow = ChessWindow();
	chessWindow.show();
	return app.exec();
}
