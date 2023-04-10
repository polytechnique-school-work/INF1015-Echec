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

std::string model::Piece::getName()
{
    return "piece";
}
