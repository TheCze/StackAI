#pragma once
#include <vector>
#include "AStarNode.h"
#include <queue>

struct OpenList {
	void AddOrUpdate(AStarNode node);
	AStarNode PopLowestCost();
	bool empty() { return heap.empty(); };
	int size() { return heap.size(); }
private:
	std::priority_queue<AStarNode> heap;
};