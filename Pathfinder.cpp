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
#include "NavRecConnection.h"
#include "NavRec.h"

typedef std::shared_ptr<NavRec> nav_ptr;
float sqr2 = 1.41421356237f;
std::shared_ptr<Path> Pathfinder::GetPath(World& world, Pos2D start, Pos2D target)
{
	nav_ptr target_nav_rec = GetNavRecAtPos(target);
	nav_ptr current_nav_rec = GetNavRecAtPos(start);
	if (!target_nav_rec)
		return nullptr;
	if (!HasThisNavRecBeenCalculated(target_nav_rec->start.hash())) {
		target_nav_rec->DepthSearchConnections(0, target_nav_rec->start.hash());
		searched_navrecs.insert(target_nav_rec->start.hash());
	}
	if (!IsReachable(world, start, target)) {
		return nullptr;
	}
	OpenList openlist;
	ClosedList closedlist;
	anode_ptr start_node(new AStarNode(world.GetTile(start)));
	openlist.AddOrUpdate(*start_node);
	while (!openlist.empty()) {		
		AStarNode current_node = openlist.PopLowestCost();
		current_nav_rec = UpdateNavRecIfChanged(current_nav_rec, current_node.tile.pos_);
		if (current_node.tile.pos_ == target) {
			return ReversePathFromTarget(current_node);
		}
		auto adjacents = world.GetAdjacents(current_node.tile.pos_);
		anode_ptr cur(new AStarNode(current_node));
		for (auto& t : adjacents) {
			float pathcost = current_node.pathcost + t.GetTileCost() * DiagonalMod(current_node.tile.pos_, t.pos_);
			AStarNode next = AStarNode(pathcost + Heuristic(t.pos_, target, current_nav_rec, target_nav_rec), pathcost, cur, t);
			if(!closedlist.contains(next))
				openlist.AddOrUpdate(next);
		}
		closedlist.add(current_node);	
	}	
	return nullptr;
}

bool Pathfinder::HasThisNavRecBeenCalculated(int target) {
	return searched_navrecs.find(target) != searched_navrecs.end();
}

nav_ptr Pathfinder::UpdateNavRecIfChanged(nav_ptr& navrec, Pos2D position) {
	if (navrec->contains(position))
		return navrec;
	else
		return GetNavRecAtPos(position);

}

bool Pathfinder::IsReachable(World& world, Pos2D start, Pos2D target) {
	if (!world.IsValid(start) || !world.IsValid(target))
		return false;
	if (world.GetTile(start).walkable_ == false || world.GetTile(target).walkable_ == false)
		return false;
	if (GetNavRecAtPos(start)->GetHeuristicTo(GetNavRecAtPos(target)->start.hash()) == -1)
		return false;
	return true;
}

nav_ptr Pathfinder::GetNavRecAtPos(Pos2D position)
{
	for (auto navrec : navrecs) {
		if (navrec->contains(position)) {
			return navrec;
		}
	}
	return nullptr;
}

void Pathfinder::ClearNavRecHeuristic()
{
	for (auto navrec : navrecs) {
		navrec->ClearHeuristics();
	}
	searched_navrecs.clear();
}

float Pathfinder::Heuristic(Pos2D start, Pos2D target, nav_ptr currentNav, nav_ptr targetNav) {
	float euclid_heu = SemiEuclidDistance(start,target);
	return euclid_heu;
	float nav_heu = UpdateNavRecIfChanged(currentNav, start)->GetHeuristicTo(target.hash());
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

const float Pathfinder::DiagonalMod(Pos2D& a, Pos2D& b)
{
	if (ManhattanDistance(a, b) == 1)
		return 1;
	else
		return sqr2;
}

const void Pathfinder::UpdateNavRec(World& world, Pos2D location) {
	navrecs.clear();
	int width = world.kTilesWidth - location.x;
	int height = world.kTilesHeight - location.y;
		for (int y = location.y; y < height; y++) {
			for (int x = location.x; x < width; x++) {
				if (world.GetTile(x, y).walkable_) {
					if (!IsInNavRec(Pos2D(x, y))) {						
						auto navrec = CreateNavRecFromPos(world, Pos2D(x,y));
						if (navrec->IsValid()) {
							navrecs.push_back(navrec);
						}
						else
							std::cout << "Invalid";
					}
				}
			}
		}
		UpdateNavRecConnections(world);
}


//Search adjacent to each navrec in all four directions for other Navrecs
void Pathfinder::UpdateNavRecConnections(World& world)
{
	for (auto& navrec : navrecs) {
		Pos2D start = navrec->GetCornerTopLeft();
		Pos2D target = navrec->GetCornerTopRight();
		start.y -= 1;
		target.y -= 1;
		if (world.IsValid(start) && world.IsValid(target))
			FindNavRecsOnLine(navrec, start, target);
		start = navrec->GetCornerTopLeft();
		target = navrec->GetCornerBottomLeft();
		start.x -= 1;
		target.x -= 1;
		if (world.IsValid(start) && world.IsValid(target))
			FindNavRecsOnLine(navrec, start, target);
		start = navrec->GetCornerTopRight();
		target = navrec->GetCornerBottomRight();
		start.x += 1;
		target.x += 1;
		if (world.IsValid(start) && world.IsValid(target))
			FindNavRecsOnLine(navrec, start, target);
		start = navrec->GetCornerBottomLeft();
		target = navrec->GetCornerBottomRight();
		start.y += 1;
		target.y += 1;
		if (world.IsValid(start) && world.IsValid(target))
			FindNavRecsOnLine(navrec, start, target);
	}
}

//Search for a navrec between two Pos2Ds and add a connection to a given navrec
void Pathfinder::FindNavRecsOnLine(nav_ptr navrec, Pos2D start, Pos2D target) {
	while (start != target) {
		AddNavConnectionAtPos(start, navrec);
		start.MoveTowards(target);
	}
	AddNavConnectionAtPos(target, navrec);
}

void Pathfinder::AddNavConnectionAtPos(const Pos2D& start, nav_ptr& navrec)
{
	nav_ptr neighbor = GetNavRecAtPos(start);
	if (neighbor != nullptr) {
		std::shared_ptr<NavRecConnection> conn(new NavRecConnection(navrec, neighbor));
		navrec->AddConnection(conn);
	}
}

const bool Pathfinder::IsInNavRec(Pos2D location) {
	for (auto navrec : navrecs) {
		if (navrec->contains(location)) {
			return true;
		}
	}
	return false;
}

const nav_ptr Pathfinder::CreateNavRecFromPos(World& world, Pos2D location) {
	int width = world.kTilesWidth;
	int height = world.kTilesHeight;
	for (int x = location.x; x < width; x++) {
		if (!world.GetTile(x, location.y).walkable_ || IsInNavRec(Pos2D(x,location.y))) {
			width = x;
			break;
		}
	}
	for (int y = location.y; y < height; y++) {
		for (int x = location.x; x < width; x++) {
			if (!world.GetTile(x, y).walkable_ || IsInNavRec(Pos2D(x, y))) {
				height = y;
				break;
			}
		}
	}
	height -= location.y;
	width -= location.x;
	Pos2D size(width, height);
	nav_ptr nav(new NavRec(location, size));
	return nav;
}