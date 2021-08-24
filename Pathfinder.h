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
	void CheckNavRecHeuristics(nav_ptr& target_nav_rec);
	bool HasThisNavRecBeenCalculated(int target);
	std::vector<nav_ptr> navrecs;
	bool IsReachable(World& world, Pos2D start, Pos2D target);
	sf::RenderWindow* window_;
	Spritesheet* font_;
	const void UpdateNavRec(World& world, Pos2D location);
	void UpdateNavRecConnections(World& world);
	void FindNavRecsOnLine(nav_ptr navrec, Pos2D start, Pos2D target);
	void AddNavConnectionAtPos(const Pos2D& start, nav_ptr& navrec);
	const bool IsInNavRec(Pos2D location);
	const nav_ptr CreateNavRecFromPos(World& world, Pos2D location);
	static const float SemiEuclidDistance(Pos2D& start, Pos2D& target);

private:
	nav_ptr UpdateNavRecIfChanged(nav_ptr& navrec, Pos2D position);
	nav_ptr GetNavRecAtPos(Pos2D target);
	void ClearNavRecHeuristic();
	float Heuristic(Pos2D start, Pos2D target, nav_ptr currentNav, nav_ptr targetNav);
	std::shared_ptr<Path> ReversePathFromTarget(AStarNode target);
	const float ManhattanDistance(Pos2D& start, Pos2D& target);
	const float DiagonalMod(Pos2D& a, Pos2D& b);
	std::set<int> searched_navrecs;
};