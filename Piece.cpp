#include "Piece.hpp"
using namespace model;


Team Piece::getTeam()
{
    return this->team;
}

void Piece::incrementMoves()
{
    this->moves += 1;
}

void Piece::decrementMoves()
{
    this->moves -= 1;
}

bool Piece::getMoves() const
{
    return this->moves;
}

// Pas dans les lignes couvertes par les tests : utile pour la vue
std::string model::Piece::getName()
{
    return "piece";
}
