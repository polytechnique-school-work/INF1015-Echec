﻿#include <QApplication>

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


using namespace std;
using namespace model;

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	// cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.
	
	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
	#endif
	//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main après l'appel à cette fonction puisqu'il exécute uniquement les tests Google Test dans l'appel ci-dessus.
}

namespace model {

	std::ostream& operator<<(std::ostream& out, const Piece& piece) {
		piece.display(out);
		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Board& board)
	{
		static const string ligneDeSeparation = "\033[32m─────────────────────────────────────────────────────────────\033[0m\n";
		out << ligneDeSeparation << endl;
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			for (int x = 0; x < BOARD_SIZE; x++) {

				auto&& piece = board.getPiece(Location(x, y));
				if (piece.has_value()) {
					out << (**piece);
				}
				else {
					out << "X";
				}

				out << "\t";
			}

			out << endl;
		}

		out << ligneDeSeparation << endl;

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Location& loc) {
		out << "x: " << loc.first << " y: " << loc.second;
		return out;
	}

	std::ostream& operator<<(std::ostream& out, const list<Location>& locations) {
		out << "Locations: " << endl;
		for (auto&& loc : locations)
		{
			out << "\t" << loc << endl;
		}
		return out;
	}

}


int main(int argc, char *argv[])
{
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	initialiserBibliothequeCours(argc, argv);

	Board board = Board();
	Piece& rock = (**board.getPiece(Location(0, 0)));

	cout << board;
	board.movePiece({ 0,0 }, { 0, 1 });

	PieceContainer& king = board.getPiece(Location(0, 1));

	cout << board.calculatePossiblePosition({ 0, 1 });

	cout << board;
}
