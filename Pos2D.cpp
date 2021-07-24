#include <ostream>
#include "Pos2D.h"
std::ostream& operator<<(std::ostream& os, const Pos2D pos)
{
	os << pos.x << "/" << pos.y;
	return os;
}