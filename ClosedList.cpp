#pragma once
#include "ClosedList.h"

bool ClosedList::contains(AStarNode new_node)
{
	for (auto& node : list) {
		if (node.tile.pos_ == new_node.tile.pos_)
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
		std::cout << "Pos: " << node.tile.pos_.x << " / " << node.tile.pos_.y <<" (From: "
			<< node.previous->tile.pos_.x << " / " << node.previous->tile.pos_.y << ")" << " Cost: "<< node.pathCost << std::endl;
		else
			std::cout << "Pos: " << node.tile.pos_.x << " / " << node.tile.pos_.y << " (START)" << std::endl;
	}
	std::cout << "[[[[[[[ ]]]]]]]]" << std::endl;
}
