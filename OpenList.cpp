#pragma once
#include "OpenList.h"

void OpenList::AddOrUpdate(AStarNode new_node)
{
	heap.push(new_node);
}

AStarNode OpenList::PopLowestCost()
{
	auto min =  heap.top();
	heap.pop();
	return min;
}
