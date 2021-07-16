#pragma once
#include "NavRec.h"

bool NavRec::contains(Pos2D pos)
{
	if (start.x <= pos.x && start.x + size.x > pos.x)
		if (start.y <= pos.y && start.y + size.y > pos.y)
			return true;
	return false;
}
