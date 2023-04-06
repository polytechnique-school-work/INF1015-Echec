#include "Piece.hpp"
using namespace model;


Team Piece::getTeam()
{
    return this->team;
}

void Piece::setPieceMove()
{
    this->hasMove = true;
}

bool Piece::hasAlreadyMove() const
{
    return this->hasMove;
}
