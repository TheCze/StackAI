#pragma once
#include "Pos2D.h"
#include <memory>
class NavRec;
typedef std::shared_ptr<NavRec> nav_ptr;


struct NavRecConnection {
	float heuristic=-1; //ALWAYS -1 UNTIL A VALID CONNECTION HAS BEEN FOUND
	nav_ptr from;
	nav_ptr to;
	NavRecConnection(nav_ptr a, nav_ptr b) : from(a), to(b) { checkNeighbor(); }

private:
	void checkNeighbor();
	//RETURNS THE DIRECTION OF A POTENTIAL OVERLAP FROM a POV
	//-1:NONE		0:TOP	1:RIGHT		2:BELOW		3:LEFT
	const int OverLaps(Pos2D& a_start, Pos2D& a_size, Pos2D& b_start, Pos2D& b_size);
	const bool IsOnLine(Pos2D& point, Pos2D& start, Pos2D& end);
	const bool InRange(float a, float b_min, float b_max);
	float GetEstimatedCost(nav_ptr& a, nav_ptr& b);
};