#pragma once
#include "NavRecConnection.h"
#include "Pathfinder.h"
#include "Pos2D.h"

void NavRecConnection::checkNeighbor()
{
	int overlap = OverLaps(from->start, from->size, to->start, to->size);
	if (overlap != -1) {
		distance = GetEstimatedCost(from, to);
	}
}

const int NavRecConnection::OverLaps(Pos2D& a_start, Pos2D& a_size, Pos2D& b_start, Pos2D& b_size)
{
	Pos2D a_tl = a_start;
	Pos2D a_tr = Pos2D(a_start.x + a_size.x, a_start.y);
	Pos2D a_bl = Pos2D(a_start.x, a_start.y + a_size.y);
	Pos2D a_br = Pos2D(a_start.x + a_size.x, a_start.y + a_size.y);
	Pos2D b_tl = b_start;
	Pos2D b_tr = Pos2D(b_start.x + b_size.x, b_start.y);
	Pos2D b_bl = Pos2D(b_start.x, b_start.y + b_size.y);
	Pos2D b_br = Pos2D(b_start.x + b_size.x, b_start.y + b_size.y);

	//Check for literal edge cases
	if (a_tl == b_br || a_tr == b_bl || a_br == b_tl || a_bl == b_tr)
		return -1;		
	if (IsOnLine(a_tl, b_tr, b_br))
		return 3;
	if (IsOnLine(a_tl, b_bl, b_br))
		return 0;
	if (IsOnLine(a_tr, b_tl, b_bl))
		return 1;
	if (IsOnLine(a_tr, b_bl, b_br))
		return 0;
	if (IsOnLine(a_bl, b_tr, b_br))
		return 3;
	if (IsOnLine(a_bl, b_tl, b_tr))
		return 2;
	if (IsOnLine(a_br, b_tl, b_bl))
		return 1;
	if (IsOnLine(a_br, b_tl, b_tr))
		return 2;
	return -1;
}

const bool NavRecConnection::IsOnLine(Pos2D& point, Pos2D& start, Pos2D& end)
{

	if (start.x == end.x) {
		if (point.x == start.x)
			if (InRange(point.y, start.y, end.y))
				return true;
	}
	if (start.y == end.y) {
		if (point.y == start.y)
			if (InRange(point.x, start.x, end.x))
				return true;
	}
}

const bool NavRecConnection::InRange(float a, float b_min, float b_max)
{
	return a >= b_min && a <= b_max;
}

float NavRecConnection::GetEstimatedCost(nav_ptr& a, nav_ptr& b)
{
	Pos2D center_a = Pos2D(a->start.x + a->size.x / 2, a->start.y + a->size.y);
	Pos2D center_b = Pos2D(b->start.x + b->size.x / 2, b->start.y + b->size.y);
	return Pathfinder::SemiEuclidDistance(center_a, center_b);
}
