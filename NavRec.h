#pragma once
#include "Pos2D.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Randomizer.h"
#include "NavRecConnection.h"
struct NavRec {
	typedef std::shared_ptr<NavRec> nav_ptr;
	NavRec(Pos2D a, Pos2D b) : start(a), size(b) { color.a = 150; }
	Pos2D start;
	Pos2D size;
	sf::Color color = random::getRandomColor();
	float current_heuristic = -1;
	bool IsValid() { return size.x > 0 && size.y > 0; }
	bool contains(Pos2D pos);
	void AddConnection(NavRecConnection& neighbor);
	void RemoveConnection(NavRecConnection& neighbor);
private:
	std::vector<NavRecConnection> neighbors;
};