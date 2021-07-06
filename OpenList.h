#pragma once
#include <vector>
#include "AStarNode.h"
struct OpenList {
	void AddOrUpdate(AStarNode node);
	AStarNode PopLowestCost();
	void DebugPrint();
	bool empty() { return list.empty(); };
	int size() { return list.size(); }
private:
	std::vector<AStarNode> list;
};