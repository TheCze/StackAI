#pragma once
#include "Pos2D.h"
#include <memory>
#include "World.h"
#include "Path.h"
#include "Pathfinder.h"
#include <queue>
#include "AStarNode.h"
#include <cmath>
#include "OpenList.h"
#include "ASCII.h"
#include "ClosedList.h"
#include <SFML/Graphics.hpp>

typedef std::shared_ptr<NavRec> nav_ptr;
float sqr2 = 1.41421356237f;
std::shared_ptr<Path> Pathfinder::GetPath(World& world, Pos2D start, Pos2D target)
{
	if (!IsReachable(world, start, target)) {
		return nullptr;
	}
	OpenList openlist;
	ClosedList closedlist;
	anode_ptr start_node(new AStarNode(world.GetTile(start)));
	openlist.AddOrUpdate(*start_node);
	while (!openlist.empty()) {
		AStarNode current_node = openlist.PopLowestCost();
		if (current_node.tile.pos_ == target) {
			return ReversePathFromTarget(current_node);
		}
		auto adjacents = world.GetAdjacents(current_node.tile.pos_);
		anode_ptr cur(new AStarNode(current_node));
		for (Tile& t : adjacents) {
			float pathcost = current_node.pathcost + t.GetTileCost() * DiagonalMod(current_node.tile.pos_, t.pos_);
			AStarNode next = AStarNode(pathcost + Heuristic(t.pos_, target), pathcost, cur, t);
			if(!closedlist.contains(next))
				openlist.AddOrUpdate(next);
		}
		closedlist.add(current_node);	
	}	
	return nullptr;
}

bool Pathfinder::IsReachable(World& world, Pos2D start, Pos2D target) {	
	return world.GetTile(target).walkable_;
}

float Pathfinder::Heuristic(Pos2D start, Pos2D target) {
	return SemiEuclidDistance(start,target);
}

std::shared_ptr<Path> Pathfinder::ReversePathFromTarget(AStarNode target)
{
	std::shared_ptr<Path> path(new Path(target.tile.pos_));
	while (target.previous) {
		Pos2D pos = target.previous->tile.pos_;
		path->AddNode(pos);
		target = *target.previous;
	}
	path->ReversePath();
	return path;
}

const float Pathfinder::ManhattanDistance(Pos2D& start, Pos2D& target)
{
	float cost = (float)std::abs(start.x - target.x) + (float)std::abs(start.y - target.y);
	return cost;
}

const float Pathfinder::SemiEuclidDistance(Pos2D& start, Pos2D& target)
{
	float cost = 0;
	int dif_x = std::abs(start.x - target.x);
	int dif_y = std::abs(start.y - target.y);
	int dif_d = std::abs(dif_x - dif_y);
	cost += dif_d;
	cost += std::min(dif_x, dif_y) * sqr2;
	return cost;
}

const float Pathfinder::DiagonalMod(Pos2D& a, Pos2D& b)
{
	if (ManhattanDistance(a, b) == 1)
		return 1;
	else
		return sqr2;
}

void Pathfinder::CheckForDoubles(World& world) {
	int width = world.kTilesWidth;
	int height = world.kTilesHeight;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int i = 0;
			for (auto navrec : navrecs) {
				if (navrec->contains(Pos2D(x,y))) {
					++i;
				}
			}
			if(i>1){
				std::cout << "Multiple nav: " << i << " at: " << x << "/" << y << std::endl;
			}
		}
	}
}

const void Pathfinder::UpdateNavRec(World& world, Pos2D location) {
	navrecs.clear();
	std::cout << "========Initiating NavRecs========: " << std::endl;
	int width = world.kTilesWidth - location.x;
	int height = world.kTilesHeight - location.y;
		for (int y = location.y; y < height; y++) {
			for (int x = location.x; x < width; x++) {
				if (world.GetTile(x, y).walkable_) {
					if (!IsInNavRec(Pos2D(x, y))) {						
						auto navrec = FindNavRecFromPos(world, Pos2D(x,y));
						if (navrec->IsValid()) {
							navrecs.push_back(navrec);
							//return;
						}
						else
							std::cout << "Unvalid";
//						location.x += navrec->size.x;
					}
				}
			}
		}
	std::cout << "Total navrecs: " << navrecs.size() << std::endl;
	CheckForDoubles(world);
}



const bool Pathfinder::IsInNavRec(Pos2D location) {
	for (auto navrec : navrecs) {
		if (navrec->contains(location)) {
			return true;
		}
	}
	return false;
}

const nav_ptr Pathfinder::FindNavRecFromPos(World& world, Pos2D location) {
	int width = world.kTilesWidth;
	int height = world.kTilesHeight;
	std::cout << "Starting new search from Pos: " << location.x << "/" << location.y << std::endl;
	std::cout << "Width: " << width << " Height: " << height <<std::endl;
	for (int x = location.x; x < width; x++) {
		std::cout << "Checking " << x << " for break ...";
		if (!world.GetTile(x, location.y).walkable_ || IsInNavRec(Pos2D(x,location.y))) {
			std::cout << "X break at: " << x;
			width = x;
			break;
		}
	}
	std::cout << std::endl;
	for (int y = location.y; y < height; y++) {
		for (int x = location.x; x < width; x++) {
			if (!world.GetTile(x, y).walkable_ || IsInNavRec(Pos2D(x, y))) {
				std::cout << " Y break at: " << y << std::endl;
				height = y;
				break;
			}
		}
	}
	height -= location.y;
	width -= location.x;
	Pos2D size(width, height);
	std::cout << "NavRec found: " << location.x << "/" << location.y << " Width/Height: " << width << "/" << height << std::endl;
	nav_ptr nav(new NavRec(location, size));
	return nav;
}