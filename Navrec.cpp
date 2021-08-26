#pragma once
#include "NavRec.h"
#include <iostream>

namespace PathfinderCZ {
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


	void NavRec::DepthSearchConnections(float connectioncost, int target)
	{
		if (GetHeuristicTo(target) > connectioncost || GetHeuristicTo(target) == -1) {
			SetHeuristicTo(target, connectioncost);
			for (auto navrec : neighbors) {
				navrec->to->DepthSearchConnections(GetHeuristicTo(target) + navrec->distance, target);
			}
		}
	}

	Pos2D NavRec::GetCornerTopLeft()
	{
		return Pos2D(start);
	}


	Pos2D NavRec::GetCornerTopRight()
	{
		return Pos2D(start.x + size.x - 1, start.y);
	}

	Pos2D NavRec::GetCornerBottomLeft()
	{
		return Pos2D(start.x, start.y + size.y - 1);
	}

	Pos2D NavRec::GetCornerBottomRight()
	{
		return Pos2D(start.x + size.x - 1, start.y + size.y - 1);
	}

	float NavRec::GetHeuristicTo(int target)
	{
		auto index = heuristics.find(target);
		if (index != heuristics.end())
			return index->second;
		else
			return -1;
	}

	void NavRec::SetHeuristicTo(int target, float value) {
		auto index = heuristics.find(target);
		if (index != heuristics.end())
			index->second = value;
		else
			heuristics.insert(std::pair<int, float>(target, value));
	}

	void NavRec::ClearHeuristics()
	{
		heuristics.clear();
	}

	void NavRec::PrintHeuristics() {
		for (auto& entry : heuristics) {
			std::cout << "To " << entry.first << " cost " << entry.second << std::endl;
		}
	}
}