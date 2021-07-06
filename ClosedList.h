#pragma once
#include "AStarNode.h"
#include <set>
class ClosedList {
public:
	std::vector<AStarNode> list;
	bool contains(AStarNode node);
	void add(AStarNode node);
	int size() { return list.size(); }
	bool empty() { return list.empty(); }
	void print();
};