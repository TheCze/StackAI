#pragma once
#include "AStarNode.h"
namespace PathfinderCZ {
	bool operator<(const AStarNode& a, const AStarNode& b)
	{
		if (a.estcost == b.estcost)
			return a.pathcost < b.pathcost;
		return a.estcost > b.estcost;
	}

	bool operator>(const AStarNode& a, const AStarNode& b)
	{
		if (a.estcost == b.estcost)
			return a.pathcost > b.pathcost;
		return a.estcost < b.estcost;
	}

	bool operator==(const AStarNode& a, const AStarNode& b)
	{
		return a.pathcost == b.pathcost && a.tile.pos_.x == b.tile.pos_.x && a.tile.pos_.y == b.tile.pos_.y;
	}
}
