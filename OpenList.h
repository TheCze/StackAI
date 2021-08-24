#pragma once
#include <vector>
#include "AStarNode.h"
#include <queue>

struct OpenList {
	void AddOrUpdate(AStarNode node);
	AStarNode PopLowestCost();
	void DebugPrint();
	bool empty() { return heap.empty(); };
	int size() { return heap.size(); }
private:
	std::vector<AStarNode> list;
	std::priority_queue<AStarNode> heap;
};