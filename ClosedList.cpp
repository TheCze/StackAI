#pragma once
#include "ClosedList.h"

bool ClosedList::contains(AStarNode new_node)
{
	for (auto& node : list) {
		if (node.tile.m_pos == new_node.tile.m_pos)
			return true;
	}
	return false;
}

void ClosedList::add(AStarNode node)
{
	list.push_back(node);
}

void ClosedList::print()
{
	std::cout << "[[Closed List]]" << std::endl;
	for (AStarNode& node : list) {
		if(node.previous)
		std::cout << "Pos: " << node.tile.m_pos.x << " / " << node.tile.m_pos.y <<" (From: "
			<< node.previous->tile.m_pos.x << " / " << node.previous->tile.m_pos.y << ")" << " Cost: "<< node.pathCost << std::endl;
		else
			std::cout << "Pos: " << node.tile.m_pos.x << " / " << node.tile.m_pos.y << " (START)" << std::endl;
	}
	std::cout << "[[[[[[[ ]]]]]]]]" << std::endl;
}
