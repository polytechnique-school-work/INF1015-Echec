#include "Piece.hpp"


Team Piece::getTeam()
{
    return this->team;
}

void Piece::setPieceMove()
{
    this->hasAlreadyMove = true;
}
