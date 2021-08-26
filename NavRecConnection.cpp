#pragma once
#include "NavRecConnection.h"
#include "Pathfinder.h"
#include "Pos2D.h"

namespace PathfinderCZ {
	float NavRecConnection::GetEstimatedCost(const nav_ptr& a, const nav_ptr& b)
	{
		Pos2D center_a = Pos2D(a->start.x + a->size.x / 2, a->start.y + a->size.y);
		Pos2D center_b = Pos2D(b->start.x + b->size.x / 2, b->start.y + b->size.y);
		return PathfinderCZ::Pathfinder::SemiEuclidDistance(center_a, center_b);
	}
}
