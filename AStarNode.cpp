#pragma once
#include "AStarNode.h"

bool operator<(const AStarNode& a, const AStarNode& b)
{
	if (a.estCost == b.estCost)
		return a.pathCost < b.pathCost;
	return a.estCost >b.estCost;
}

bool operator>(const AStarNode& a, const AStarNode& b)
{
	if (a.estCost == b.estCost)
		return a.pathCost > b.pathCost;
	return a.estCost < b.estCost;
}

bool operator==(const AStarNode& a, const AStarNode& b)
{
	return a.pathCost == b.pathCost && a.tile.pos_.x == b.tile.pos_.x && a.tile.pos_.y == b.tile.pos_.y;
}

