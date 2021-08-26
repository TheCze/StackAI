#pragma once
#include <vector>
#include "AStarNode.h"
#include <queue>
namespace PathfinderCZ {
	struct OpenList {
		void AddOrUpdate(AStarNode new_node)
		{
			heap.push(new_node);
		}
		AStarNode PopLowestCost()
		{
			auto min = heap.top();
			heap.pop();
			return min;
		}
		bool empty() { return heap.empty(); };
		int size() { return heap.size(); }
	private:
		std::priority_queue<AStarNode> heap;
	};
}