#pragma once
#include "Pos2D.h"
#include <memory>
class NavRec;
typedef std::shared_ptr<NavRec> nav_ptr;

struct NavRecConnection {
	float distance=-1;
	nav_ptr from;
	nav_ptr to;
	NavRecConnection(nav_ptr a, nav_ptr b) : from(a), to(b){ distance=GetEstimatedCost(a, b); }
private:
	float GetEstimatedCost(const nav_ptr& a, const nav_ptr& b);
};