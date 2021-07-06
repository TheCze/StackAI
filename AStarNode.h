#pragma once
#include <memory>
#include "Tile.h"
class AStarNode {
public:
	typedef std::shared_ptr<AStarNode> anode_ptr;
	float estCost;
	float pathCost;
	anode_ptr previous;
	Tile tile;
	AStarNode(float cost, float path, anode_ptr origin, Tile t): estCost(cost) , pathCost(path), previous(origin) , tile(t){}
	AStarNode(Tile t) : estCost(0), pathCost(0), tile(t) {}

	friend bool operator<(const AStarNode& a, const AStarNode& b);
	friend bool operator>(const AStarNode& a, const AStarNode& b);
	friend bool operator==(const AStarNode& a, const AStarNode& b);
};