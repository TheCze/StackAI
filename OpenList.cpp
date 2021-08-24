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

void OpenList::DebugPrint()
{
	std::cout << "==Open List==" << std::endl;
	for (AStarNode& node : list) {
		if (node.previous)
		std::cout << node.tile.pos_.x << " / " << node.tile.pos_.y << " (From: "
			<< node.previous->tile.pos_.x << " / " << node.previous->tile.pos_.y << ")" << std::endl
			<<"Tile: " << node.pathcost <<" Heuristic: "<< node.estcost- node.pathcost << " Total: " << node.estcost << std::endl;
		else {
			std::cout << node.tile.pos_.x << " / " << node.tile.pos_.y << " (START)" << std::endl
				<< "Tile: " << node.pathcost << " Heuristic: " << node.estcost - node.pathcost << " Total: " << node.estcost << std::endl;
		}
	}
	std::cout << "===============" << std::endl;
}
