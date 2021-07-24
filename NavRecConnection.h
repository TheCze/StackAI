#pragma once
#include "Pos2D.h"
#include "NavRec.h"
#include <iostream>
typedef std::shared_ptr<NavRec> nav_ptr;
struct NavRecConnection {
	Pos2D borderstart;
	Pos2D borderend;
	float heuristic=-1; //ALWAYS -1 UNTIL A VALID CONNECTION HAS BEEN FOUND
	nav_ptr from;
	nav_ptr to;
	NavRecConnection(nav_ptr a, nav_ptr b) : from(a), to(b) { checkNeighbor(); }

	void checkNeighbor() {
		Pos2D start  = from->start;
		Pos2D startouter = start + from->size;

		Pos2D target = to->start;
		Pos2D targetouter = target + to->size;

		if (targetouter.x == start.x || startouter.x == target.x) {		//CHECK LEFT AND RIGHT
			if (IsOnLine(target.y, start.y, startouter.y) || IsOnLine(targetouter.y, start.y, startouter.y)
				|| IsOnLine(start.y, target.y, targetouter.y) || IsOnLine(startouter.y, target.y, targetouter.y)) { //CHECK Y AXIS
				heuristic = GetEstimatedCost(from->size.y, to->size.y);
				float borderstart_y = (start.y>target.y) ? start.y : target.y;
				float borderend_y = (startouter.y < targetouter.y) ? startouter.y : targetouter.y;
				float border_x = (targetouter.x == start.x) ? start.x : startouter.x-1;
				borderstart.x = border_x;
				borderstart.y = borderstart_y;
				borderend.x = border_x;
				borderend.y = borderend_y;
				std::cout << "Connection of NavRec at " << start.x << "/" << start.y << " to : " << startouter.x << " / " << startouter.y << std::endl;
				std::cout << "Border from : " << borderstart.x << "/" << borderstart.y << " to : " << borderend.x << " / " << borderend.y <<std::endl;
			}
			else {
				std::cout << "Not up/down to each other" << std::endl;
			}
		}
		else {
			std::cout << "Not right/left to each other" << std::endl;
		}
	}

	bool IsOnLine(float y, float y_start, float y_end) {
		return (y > y_start && y < y_end);
	}

	float GetEstimatedCost(float widtha, float widthb) {
		return (widtha + widthb) / 2;
	}
};