#pragma once
#include <vector>
#include "AStarNode.h"
class OpenList {
public:
	std::vector<AStarNode> list;
	void addOrUpdate(AStarNode node);
	AStarNode popLowestCost();
	void print();
	bool empty() { return list.empty(); };
	int size() { return list.size(); }
};