#include "Piece.hpp"


Team Piece::getTeam()
{
    return this->team;
}

void Piece::setPieceMove()
{
    this->hasMove = true;
}

bool Piece::hasAlreadyMove()
{
    return this->hasMove;
}
