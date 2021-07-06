#pragma once
#include "AStarNode.h"
#include <set>
struct ClosedList {
public:
	bool contains(AStarNode node);
	void add(AStarNode node);
	int size() { return list.size(); }
	bool empty() { return list.empty(); }
	void DebugPrint();
private:
	std::vector<AStarNode> list;
};