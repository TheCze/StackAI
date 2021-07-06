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

float sqr2 = 1.41421356237f;
std::shared_ptr<Path> Pathfinder::getPath(World& world, Pos2D start, Pos2D target)
{
	return find_astar(world, start, target);
}

std::shared_ptr<Path> Pathfinder::find_astar(World& world, Pos2D start, Pos2D target)
{	
	if (!world.getPos(target).walkable)
		return nullptr;
	//world.clearWorld();
	sf::Clock clock;
	clock.restart();
	//float step_time = 0.05f;
	OpenList openlist;
	ClosedList closedlist;
	anode_ptr start_node(new AStarNode(world.getPos(start)));
	openlist.addOrUpdate(*start_node);
	int i = 0;
	while (!openlist.empty()) {
		i++;
		AStarNode current = openlist.popLowestCost();
		if (current.tile.m_pos == target) {
			auto path = reverse_path_from(current);
			int length = path->length();
			float time = clock.getElapsedTime().asMilliseconds();
			if (time > 200) {
			std::cout << "Path took too long: " << time << " ms"<<std::endl;
			std::cout << "Path took : " << time << " ms" << std::endl;
			std::cout << "Found path length: " << length << " steps, elapsed time: " << time << " mms"<<std::endl;
			std::cout << "MS per TILE: " << length / time << std::endl;
			}
			return path;
		}
		auto adjacents = world.get_adjacents(current.tile.m_pos);
		for (Tile& t : adjacents) {
			float pathcost = current.pathCost + t.GetTileCost() * diagonal_mod(current.tile.m_pos, t.m_pos);
			//pathcost *= diagonal_mod(current.tile.m_pos, t.m_pos);
			float heur = heuristic(t.m_pos, target);
			float estcost = pathcost + heur;
			anode_ptr cur(new AStarNode(current));
			AStarNode next = AStarNode(estcost, pathcost, cur, t);
			if(!closedlist.contains(next))
				openlist.addOrUpdate(next);
		}
		current.estCost = 0;
		closedlist.add(current);
		//while (clock.getElapsedTime().asSeconds() < step_time) {			
		//}			
		//clock.restart();
		//displayList(world, openlist.list, ASCII::dither_min, sf::Color(150,150,0,200),target);
		//displayList(world, closedlist.list, ASCII::dither_max, sf::Color::Green, target);
		//debug_render(window, world, font, start, target);		
	}	
	std::cout << "COULD NOT FIND PATH! Time: " << clock.getElapsedTime().asMilliseconds() <<" ms" << std::endl;
	std::cout << "FROM: " << start.x << "/" << start.y << std::endl;
	std::cout << "TO  : " << target.x << "/" << target.y << std::endl;
	std::cout << "OPEN LIST SIZE: " << openlist.size() << std::endl;
	std::cout << "CLOSED LIST SIZE: " << closedlist.size() << std::endl;
	return nullptr;
}

float Pathfinder::heuristic(Pos2D start, Pos2D target) {
	return quick_euclid_distance(start,target);
}

std::shared_ptr<Path> Pathfinder::reverse_path_from(AStarNode target)
{
	std::shared_ptr<Path> path(new Path(target.tile.m_pos));
	while (target.previous) {
		Pos2D pos = target.previous->tile.m_pos;
		path->addNode(pos);
		target = *target.previous;
	}
	path->reverse();
	return path;
}

std::shared_ptr<Path> Pathfinder::get_trivial_path(World& world, Pos2D start, Pos2D target)
{
	std::shared_ptr<Path> path(new Path(start));
	while (start != target) {
		start = findNext(start, target);
		path->addNode(start);
	}
	return path;
}


float Pathfinder::manhattan_distance(Pos2D start, Pos2D target)
{
	float cost = (float)std::abs(start.x - target.x) + (float)std::abs(start.y - target.y);
	return cost;
}

float Pathfinder::quick_euclid_distance(Pos2D start, Pos2D target)
{
	float cost = 0;
	int dif_x = std::abs(start.x - target.x);
	int dif_y = std::abs(start.y - target.y);
	int dif_d = std::abs(dif_x - dif_y);
	cost += dif_d;
	cost += std::min(dif_x, dif_y) * sqr2;
	return cost;
}

float Pathfinder::euclid_distance(Pos2D start, Pos2D target)
{
	float dif_x = std::abs(start.x - target.x);
	float dif_y = std::abs(start.y - target.y);
	float cost = std::sqrt(dif_x*dif_x + dif_y*dif_y);
	return cost;
}

float Pathfinder::diagonal_mod(Pos2D a, Pos2D b)
{
	if (manhattan_distance(a, b) == 1)
		return 1;
	else
		return sqr2;
}

void Pathfinder::debug_render(sf::RenderWindow* window, World& world, Spritesheet* font, Pos2D start, Pos2D target)
{
	window->clear();
	ASCIISymbol p = ASCIISymbol(ASCII::double_bang, Color(50, 20, 150, 250));
	p.draw(*window, *font, (float)target.x, (float)target.y);
	for (int x = 0; x < settings::WORLD_WIDTH; x++) {
		for (int y = 0; y < settings::WORLD_HEIGHT; y++) {
			world.getPos(x, y).m_symbol.draw(*window, *font, x, y);
		}
	}
	ASCIISymbol at = ASCIISymbol(ASCII::face, Color(255, 00, 0, 255));
	at.draw(*window, *font, (float)start.x, (float)start.y);
	window->display();	
}

void Pathfinder::displayList(World& world, std::vector<AStarNode>& list, int symbol, sf::Color color, Pos2D target)
{
	for (AStarNode& node : list) {
		Pos2D pos = node.tile.m_pos;
	//	float h = heuristic(node.tile.m_pos, target);
	//	color.g = h;
	//	color.b = h;
		Tile t = Tile(ASCIISymbol(symbol, color),pos);
		world.getPos(pos.x, pos.y).m_symbol.setColor(color);
	}
}

Pos2D Pathfinder::findNext(Pos2D start, Pos2D target)
{
	if (start.x > target.x)
		start.x--;
	else if (start.x < target.x)
		start.x++;
	else if (start.y > target.y)
		start.y--;
	else if (start.y < target.y)
		start.y++;
	return start;
}
