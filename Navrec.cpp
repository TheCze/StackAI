#pragma once
#include "NavRec.h"
#include <iostream>

bool NavRec::contains(Pos2D pos)
{
	if (start.x <= pos.x && start.x + size.x > pos.x)
		if (start.y <= pos.y && start.y + size.y > pos.y)
			return true;
	return false;
}

void NavRec::AddConnection(std::shared_ptr<NavRecConnection> neighbor)
{
	for (auto& n : neighbors) {
		if (n->to->start == neighbor->to->start) {
			return;		
		}
	}
	neighbors.push_back(neighbor);
}


void NavRec::DepthSearchConnections(float connectioncost)
{
	if (current_heuristic > connectioncost ||current_heuristic == -1) {
		current_heuristic = connectioncost;
		for (auto navrec : neighbors) {
			navrec->to->DepthSearchConnections(current_heuristic + navrec->distance);
		}
	}
}

Pos2D NavRec::GetCornerTopLeft()
{
	return Pos2D(start);
}

Pos2D NavRec::GetCornerTopRight()
{
	return Pos2D(start.x+size.x-1,start.y);
}

Pos2D NavRec::GetCornerBottomLeft()
{
	return Pos2D(start.x, start.y+size.y-1);
}

Pos2D NavRec::GetCornerBottomRight()
{
	return Pos2D(start.x + size.x-1, start.y + size.y-1);
}
