#pragma once
#include <memory>
#include "Tile.h"
struct AStarNode {

	typedef std::shared_ptr<AStarNode> anode_ptr;
	float estcost;
	float pathcost;
	anode_ptr previous;
	Tile tile;
	AStarNode(float cost, float path, anode_ptr origin, Tile t): estcost(cost) , pathcost(path), previous(origin) , tile(t){}
	AStarNode(Tile t) : estcost(0), pathcost(0), tile(t) {}

	friend bool operator<(const AStarNode& a, const AStarNode& b);
	friend bool operator>(const AStarNode& a, const AStarNode& b);
	friend bool operator==(const AStarNode& a, const AStarNode& b);
};