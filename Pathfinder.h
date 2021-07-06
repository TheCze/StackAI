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
	std::shared_ptr<Path> getPath(World& world, Pos2D start, Pos2D target);
	sf::RenderWindow* window;
	Spritesheet* font;

private:
	Pos2D findNext(Pos2D start, Pos2D target);
	std::shared_ptr<Path> get_trivial_path(World& world, Pos2D start, Pos2D target);
	std::shared_ptr<Path> find_astar(World& world, Pos2D start, Pos2D target);
	float heuristic(Pos2D start, Pos2D target);
	std::shared_ptr<Path> reverse_path_from(AStarNode target);
	float manhattan_distance(Pos2D start, Pos2D target);
	float quick_euclid_distance(Pos2D start, Pos2D target);
	float euclid_distance(Pos2D start, Pos2D target);
	float diagonal_mod(Pos2D a, Pos2D b);
	void debug_render(sf::RenderWindow* window, World& world, Spritesheet* font, Pos2D start, Pos2D target);
	void displayList(World& world, std::vector<AStarNode>& list, int symbol, sf::Color color, Pos2D target);

};