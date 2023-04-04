#include "Pawn.hpp"
std::list<Location> Pawn::getPossiblePositions() const
{
	return std::list<Location>();
}
void Pawn::display(std::ostream& out) const {
	out << "Pawn" << std::endl;
}