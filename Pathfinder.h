#pragma once
#include "Path.h"
#include <memory>
#include <queue>
#include <set>
#include "AStarNode.h"
#include "Pos2D.h"
class World;
typedef std::shared_ptr<AStarNode> anode_ptr;
class Pathfinder {
public:
	std::shared_ptr<Path> GetPath(World& world, Pos2D start, Pos2D target);
	sf::RenderWindow* window_;
	Spritesheet* font_;

private:
	std::shared_ptr<Path> GetTrivialPath(World& world, Pos2D start, Pos2D target);
	std::shared_ptr<Path> FindAstar(World& world, Pos2D start, Pos2D target);
	float Heuristic(Pos2D start, Pos2D target);
	std::shared_ptr<Path> ReversePathFromTarget(AStarNode target);
	float ManhattenDistance(Pos2D start, Pos2D target);
	float SemiEuclidDistance(Pos2D start, Pos2D target);
	float EuclidDistance(Pos2D start, Pos2D target);
	float DiagonalMod(Pos2D a, Pos2D b);
	void DebugRender(sf::RenderWindow* window, World& world, Spritesheet* font, Pos2D start, Pos2D target);
	void DisplayList(World& world, std::vector<AStarNode>& list, int symbol, sf::Color color, Pos2D target);
};