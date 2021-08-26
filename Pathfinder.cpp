#pragma once
#include "Pos2D.h"
#include <memory>
#include "World.h"
#include "Path.h"
#include "Pathfinder.h"
#include "AStarNode.h"
#include <cmath>
#include "OpenList.h"
#include "ClosedList.h"
#include <SFML/Graphics.hpp>
#include "NavRec.h"
#include "NavRecSystem.h"

typedef std::shared_ptr<NavRec> nav_ptr;
float sqr2 = 1.41421356237f;
std::shared_ptr<Path> Pathfinder::GetPath(World& world, Pos2D start, Pos2D target)
{
	nav_ptr target_nav_rec = navrecsystem.GetNavRecAtPos(target);
	nav_ptr current_nav_rec = navrecsystem.GetNavRecAtPos(start);
	if (!target_nav_rec)
		return nullptr;
	navrecsystem.CheckNavRecHeuristics(target_nav_rec);
	if (!IsReachable(world, start, target)) {
		return nullptr;
	}
	OpenList openlist;
	ClosedList closedlist;
	anode_ptr start_node(new AStarNode(world.GetTile(start)));
	openlist.AddOrUpdate(*start_node);
	while (!openlist.empty()) {
		AStarNode current_node = openlist.PopLowestCost();
		if (closedlist.contains(current_node))
			continue;
		current_nav_rec = navrecsystem.UpdateNavRecIfChanged(current_nav_rec, current_node.tile.pos_);
		if (current_node.tile.pos_ == target) {
			return ReversePathFromTarget(current_node);
		}
		auto adjacents = world.GetAdjacents(current_node.tile.pos_);
		anode_ptr cur(new AStarNode(current_node));
		for (auto& t : adjacents) {
			float pathcost = current_node.pathcost + t.GetTileCost() * DiagonalMod(current_node.tile.pos_, t.pos_);
			float heuristic = Heuristic(t.pos_, target, current_nav_rec, target_nav_rec);
			AStarNode next = AStarNode(pathcost + heuristic, pathcost, cur, t);
			if (!closedlist.contains(next))
				openlist.AddOrUpdate(next);
		}
		closedlist.add(current_node);
	}
	return nullptr;
}



bool Pathfinder::IsReachable(World& world, Pos2D start, Pos2D target) {
	if (!world.IsValid(start) || !world.IsValid(target))
		return false;
	if (world.GetTile(start).walkable_ == false || world.GetTile(target).walkable_ == false)
		return false;
	if (navrecsystem.GetNavRecAtPos(start)->GetHeuristicTo(navrecsystem.GetNavRecAtPos(target)->start.hash()) == -1)
		return false;
	return true;
}


float Pathfinder::Heuristic(Pos2D start, Pos2D target, nav_ptr currentNav, nav_ptr targetNav) {
	float euclid_heu = SemiEuclidDistance(start, target);
	return euclid_heu;
	float nav_heu = navrecsystem.UpdateNavRecIfChanged(currentNav, start)->GetHeuristicTo(target.hash());
	return (euclid_heu + nav_heu) * 0.5f;
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

const void Pathfinder::MapChangedAt(World& world, Pos2D pos)
{
	navrecsystem.UpdateNavRec(world, pos);
}

const float Pathfinder::DiagonalMod(Pos2D& a, Pos2D& b)
{
	if (ManhattanDistance(a, b) == 1)
		return 1;
	else
		return sqr2;
}
