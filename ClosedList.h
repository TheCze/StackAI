#pragma once
#include "AStarNode.h"
#include <set>
#include <unordered_set>

struct ClosedList {
public:
	bool contains(AStarNode node);
	void add(AStarNode node);
	int size() { return list.size(); }
	bool empty() { return list.empty(); }
	void DebugPrint();
private:
	std::vector<AStarNode> list;
	std::unordered_set<float> set;

};