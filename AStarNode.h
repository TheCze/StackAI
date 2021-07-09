#pragma once
#include <memory>
#include "Tile.h"
struct AStarNode {
	typedef std::shared_ptr<AStarNode> anode_ptr;
	float estcost;
	float pathcost;
	anode_ptr previous;
	Tile tile;
	std::string name = "";
	AStarNode(float cost, float path, anode_ptr origin, Tile t): estcost(cost), pathcost(path), previous(origin), tile(t) { ; }
	AStarNode(Tile t) : estcost(0), pathcost(0), tile(t) {  }

	friend bool operator<(const AStarNode& a, const AStarNode& b);
	friend bool operator>(const AStarNode& a, const AStarNode& b);
	friend bool operator==(const AStarNode& a, const AStarNode& b);

	int GetCantor() {
		int x = tile.pos_.x;
		int y = tile.pos_.y;
		return (x + y) * (x + y + 1) / 2 + y;
	}
};