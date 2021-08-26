#pragma once
#include "AStarNode.h"
#include <set>
#include <unordered_set>

namespace PathfinderCZ{
struct ClosedList {
public:
	int size() { return list.size(); }
	bool empty() { return list.empty(); }
	bool contains(AStarNode new_node)
	{
		return set.find(new_node.GetCantor()) != set.end();
	}
	void add(AStarNode node)
	{
		list.push_back(node);
		set.insert(node.GetCantor());
	}
private:
	std::vector<AStarNode> list;
	std::unordered_set<int> set;

};
}