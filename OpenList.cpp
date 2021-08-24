#pragma once
#include "OpenList.h"

void OpenList::AddOrUpdate(AStarNode new_node)
{
	for (AStarNode& node : list) {
		if (node.tile.pos_ == new_node.tile.pos_) {
			if (node.pathcost > new_node.pathcost) {
				node.pathcost = new_node.pathcost;
				return;
			}
			return;
		}
	}
	list.push_back(new_node);
}

AStarNode OpenList::PopLowestCost()
{
	auto low_point = std::max_element(list.begin(),list.end());
	AStarNode lowest = *low_point;
	list.erase(low_point);
	return lowest;
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
