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
	return a.pathCost == b.pathCost && a.tile.m_pos.x == b.tile.m_pos.x && a.tile.m_pos.y == b.tile.m_pos.y;
}

