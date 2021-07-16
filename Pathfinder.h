#pragma once
#include "Path.h"
#include <memory>
#include <queue>
#include <set>
#include "AStarNode.h"
#include "Pos2D.h"
#include "NavRec.h"
class World;
typedef std::shared_ptr<AStarNode> anode_ptr;
typedef std::shared_ptr<NavRec> nav_ptr;
class Pathfinder {
public:
	std::shared_ptr<Path> GetPath(World& world, Pos2D start, Pos2D target);
	std::vector<nav_ptr> navrecs;
	bool IsReachable(World& world, Pos2D start, Pos2D target);
	sf::RenderWindow* window_;
	Spritesheet* font_;
	const void UpdateNavRec(World& world, Pos2D location);

	const bool IsInNavRec(Pos2D location);

	const nav_ptr FindNavRecFromPos(World& world, Pos2D location);

private:
	float Heuristic(Pos2D start, Pos2D target);
	std::shared_ptr<Path> ReversePathFromTarget(AStarNode target);
	const float ManhattanDistance(Pos2D& start, Pos2D& target);
	const float SemiEuclidDistance(Pos2D& start, Pos2D& target);
	const float DiagonalMod(Pos2D& a, Pos2D& b);
	void CheckForDoubles(World& world);
};